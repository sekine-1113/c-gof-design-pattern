#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum _EventType {
    Follow,
    Favorite,
} EventType;

typedef struct _Event {
    EventType type;
    char* description;
} Event;

Event events[2] = {
    { Follow, "Follow!" },
    { Favorite, "Favorite!" }
};

typedef struct _Subscriber {
    unsigned int id;
    void (*update)(struct _Subscriber* self, Event event);
} Subscriber;

void update(struct _Subscriber* self, Event event) {
    switch (event.type) {
    case Follow:
        printf("Follow Event(%d): %s\n", self->id, event.description);
        break;
    case Favorite:
        printf("Favorite Event(%d): %s\n", self->id, event.description);
        break;
    default:
        break;
    }
}


typedef struct _Publisher {
    unsigned int length;
    unsigned int maxLength;
    Subscriber* subscribers;
    void (*subscribe)(struct _Publisher* self, Subscriber subscriber);
    void (*unsubscribe)(struct _Publisher* self, Subscriber subscriber);
    void (*notify)(struct _Publisher* self, Event event);
} Publisher;

void subscribe(struct _Publisher* self, Subscriber subscriber) {
    if (self->length >= self->maxLength) {
        self->maxLength *= 2;
        self->subscribers = (Subscriber*)realloc(self->subscribers, sizeof(Subscriber)*self->maxLength);
    }
    self->subscribers[self->length++] = subscriber;
}

void unsubscribe(struct _Publisher* self, Subscriber subscriber) {
    int foundIndex = -1;
    for (int i=0; i<self->length; i++) {
        if (self->subscribers[i].id == subscriber.id) {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex != -1) {
        for (int i=foundIndex; i<self->length-1; i++) {
            self->subscribers[i] = self->subscribers[i+1];
        }
        self->length--;
    }
}

void notify(struct _Publisher* self, Event event) {
    for (int i=0; i<self->length; i++) {
        self->subscribers[i].update(&self->subscribers[i], event);
    }
}

Publisher* new_Publisher(unsigned int maxLength) {
    Publisher* publisher = (Publisher*)malloc(sizeof(Publisher));
    publisher->length = 0;
    publisher->maxLength = maxLength;
    publisher->subscribers = (Subscriber*)malloc(sizeof(Subscriber)*maxLength);
    publisher->subscribe = subscribe;
    publisher->unsubscribe = unsubscribe;
    publisher->notify = notify;
    return publisher;
}

void delete_Publisher(Publisher* publisher) {
    free(publisher->subscribers);
    free(publisher);
}


int main(void){
    srand((unsigned int)time(NULL));

    Publisher* pub = new_Publisher(4);
    Subscriber sub1 = { rand(), update };
    Subscriber sub2 = { rand(), update };
    Subscriber sub3 = { rand(), update };

    pub->subscribe(pub, sub1);
    pub->subscribe(pub, sub2);
    pub->subscribe(pub, sub3);
    pub->notify(pub, events[0]);

    pub->unsubscribe(pub, sub2);
    pub->notify(pub, events[1]);

    delete_Publisher(pub);
    return 0;
}
