#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define definePrototype(type)\
typedef struct _##type##Prototype{\
    type* (*clone)(type* self);\
} type##Prototype

typedef struct _User User;
definePrototype(User);

typedef struct _User {
    char* name;
    unsigned int age;
    UserPrototype* prototype;
} User;
User* cloneUser(User* self);
User* new_User(char* name, int age);
void delete_User(User* user);

static UserPrototype userPrototype = { cloneUser };

int main(void) {
    User* user1 = new_User("Alice", 23);
    if (user1 == NULL) exit(1);
    User* user2 = user1->prototype->clone(user1);
    if (user2 == NULL) exit(1);

    printf("user1: (%s, %d)\nuser2: (%s, %d)\n", user1->name, user1->age, user2->name, user2->age);

    delete_User(user1);
    delete_User(user2);
    return 0;
}

User* cloneUser(User* self) {
    User* target = (User*)malloc(sizeof(User));
    if (target == NULL) return NULL;
    target->name = strdup(self->name);
    if (target->name == NULL) {
        free(target);
        return NULL;
    }
    target->age = self->age;
    target->prototype = self->prototype;
    return target;
}

User* new_User(char* name, int age) {
    User* user = (User*)malloc(sizeof(User));
    if (user == NULL) return NULL;
    user->name = strdup(name);
    if (user->name == NULL) {
        free(user);
        return NULL;
    }
    user->age = age;
    user->prototype = &userPrototype;
    return user;
}

void delete_User(User* user) {
    free(user->name);
    free(user);
}
