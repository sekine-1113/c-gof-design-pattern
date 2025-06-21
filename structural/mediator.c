#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _User User;
typedef struct _ChatRoom ChatRoom;

typedef struct _User {
    char* name;
    ChatRoom* chatRoom;
    void (*send)(struct _User* self, const char* message);
    void (*receive)(struct _User* self, const char* message, const char* from);
} User;

typedef struct _ChatRoom {
    User* users[32];
    int userCount;
    void (*sendMessage)(struct _ChatRoom* self, const char* message, User* sender);
    void (*join)(struct _ChatRoom* self, User* user);
} ChatRoom;

void send(User* self, const char* message);
void receive(User* self, const char* message, const char* from);
User* new_User(const char* name, ChatRoom* chatRoom);
void delete_User(User* user);

void sendMessage(ChatRoom* self, const char* message, User* sender);
void join(ChatRoom* self, User* user);

int main(void) {
    ChatRoom chatRoom = { .userCount = 0, .sendMessage = sendMessage, .join = join };
    User* alice = new_User("Alice", &chatRoom);
    User* bob = new_User("Bob", &chatRoom);
    User* charlie = new_User("Charlie", &chatRoom);

    alice->send(alice, "Hello! This is Alice!");
    bob->send(bob, "Hey! Alice!");
    charlie->send(charlie, "Hello!");

    delete_User(alice);
    delete_User(bob);
    delete_User(charlie);
    return 0;
}

void send(User* self, const char* message) {
    self->chatRoom->sendMessage(self->chatRoom, message, self);
}

void receive(User* self, const char* message, const char* from) {
    printf("[%s] %s: %s\n", self->name, from, message);
}

User* new_User(const char* name, ChatRoom* chatRoom) {
    User* user = (User*)malloc(sizeof(User));
    user->name = strdup(name);
    user->chatRoom = chatRoom;
    user->send = send;
    user->receive = receive;
    user->chatRoom->join(user->chatRoom, user);
    return user;
}

void delete_User(User* user) {
    free(user->name);
    free(user);
}

void sendMessage(ChatRoom* self, const char* message, User* sender) {
    for (int i=0; i<self->userCount; i++) {
        if (self->users[i] != sender) {
            self->users[i]->receive(self->users[i], message, sender->name);
        }
    }
}

void join(ChatRoom* self, User* user) {
    self->users[self->userCount++] = user;
}
