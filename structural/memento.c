#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define defineCaretaker(type) typedef struct _Caretaker##type {\
    type##Memento* buffer[8];\
    int length;\
    void (*addMemento)(struct _Caretaker##type* self, type##Memento* memento);\
    type##Memento* (*getMemento)(struct _Caretaker##type* self, int index);\
} Caretaker##type;

struct _PlayerMemento;
typedef struct _Player {
    char* name;
    unsigned int level;
    void (*showStatus)(struct _Player* self);
    struct _PlayerMemento* (*createMemento)(struct _Player* self);
    struct _Player* (*restoreMemento)(struct _Player* self, struct _PlayerMemento* memento);
} Player;
typedef struct _PlayerMemento {
    char* name;
    unsigned int level;
} PlayerMemento;
void showStatus(Player* self);
PlayerMemento* createMemento(Player* self);
Player* restoreMemento(Player* self, PlayerMemento* memento);
Player* new_Player(char* name, unsigned int level);
void delete_Player(Player* self);

defineCaretaker(Player);
void addMemento(CaretakerPlayer* self, PlayerMemento* memento);
PlayerMemento* getMemento(CaretakerPlayer* self, int index);
CaretakerPlayer* new_Caretaker(void);
void delete_Caretaker(CaretakerPlayer* caretaker);

int main(void) {
    CaretakerPlayer* caretaker = new_Caretaker();
    Player* alice = new_Player("Alice", 10);
    alice->showStatus(alice);

    PlayerMemento* memento = alice->createMemento(alice);
    caretaker->addMemento(caretaker, memento);

    alice->level = 20;
    alice->showStatus(alice);

    PlayerMemento* saved = caretaker->getMemento(caretaker, 0);
    alice->restoreMemento(alice, saved);
    alice->showStatus(alice);

    delete_Player(alice);
    delete_Caretaker(caretaker);
}

void showStatus(Player* self) {
    printf("name = %s, level = %d\n", self->name, self->level);
}

PlayerMemento* createMemento(Player* self) {
    PlayerMemento* memento = (PlayerMemento*)malloc(sizeof(PlayerMemento));
    memento->name = strdup(self->name);
    memento->level = self->level;
    return memento;
}

Player* restoreMemento(Player* self, PlayerMemento* memento) {
    free(self->name);
    self->name = strdup(memento->name);
    self->level = memento->level;
    return self;
}

Player* new_Player(char* name, unsigned int level) {
    Player* player = (Player*)malloc(sizeof(Player));
    player->name = strdup(name);
    player->level = level;
    player->showStatus = showStatus;
    player->createMemento = createMemento;
    player->restoreMemento = restoreMemento;
    return player;
}

void delete_Player(Player* self) {
    free(self->name);
    free(self);
}

void addMemento(CaretakerPlayer* self, PlayerMemento* memento) {
    self->buffer[self->length++] = memento;
}
PlayerMemento* getMemento(CaretakerPlayer* self, int index) {
    return self->buffer[index];
}

CaretakerPlayer* new_Caretaker(void) {
    CaretakerPlayer* caretaker = (CaretakerPlayer*)malloc(sizeof(CaretakerPlayer));
    caretaker->addMemento = addMemento;
    caretaker->getMemento = getMemento;
    caretaker->length = 0;
    return caretaker;
}

void delete_Caretaker(CaretakerPlayer* caretaker) {
    for (int i=0; i<caretaker->length; i++) {
        free(caretaker->buffer[i]->name);
        free(caretaker->buffer[i]);
    }
    free(caretaker);
}
