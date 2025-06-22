#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Object {
    char* name;
} Object;

typedef struct _Factory {
    Object* objects[32];
    int objectCount;
    Object* (*makeObject)(struct _Factory* self, char* name);
} Factory;

Object* makeObject(struct _Factory* self, char* name);
Factory* new_Factory(void);
void delete_Factory(Factory* factory);

int main(void) {
    Factory* factory = new_Factory();
    factory->makeObject(factory, "Hello");
    factory->makeObject(factory, "World");
    factory->makeObject(factory, "Hello");
    delete_Factory(factory);
    return 0;
}

Object* makeObject(struct _Factory* self, char* name) {
    for (int i=0; i<self->objectCount; i++) {
        if (strcmp(self->objects[i]->name, name) == 0) {
            printf("reuse: %p(name=%s)\n", self->objects[i], self->objects[i]->name);
            return self->objects[i];
        }
    }
    Object* newObject = (Object*)malloc(sizeof(Object));
    newObject->name = strdup(name);
    self->objects[self->objectCount++] = newObject;
    printf("make: %p(name=%s)\n", newObject, newObject->name);
    return newObject;
}

Factory* new_Factory(void) {
    Factory* factory = (Factory*)malloc(sizeof(Factory));
    factory->objectCount = 0;
    factory->makeObject = makeObject;
    return factory;
}

void delete_Factory(Factory* factory) {
    for (int i=0; i<factory->objectCount; i++) {
        free(factory->objects[i]->name);
        free(factory->objects[i]);
    }
    free(factory);
}
