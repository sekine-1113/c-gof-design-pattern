#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum _StateKind {
    Fine,
    Poison,
    Dead,
} StateKind;

struct _Human;
typedef struct _State {
    StateKind stateKind;
    void (*action)(struct _Human *self);
} State;

typedef struct _Human {
    char* name;
    State* state;
    void (*action)(struct _Human *self);
    struct _Human* (*changeState)(struct _Human *self, State *state);
} Human;
void fineAction(Human *self);
void poisonAction(Human *self);
void deadAction(Human *self);
void action(Human *self);
State fineState = { Fine, fineAction };
State poisonState = { Poison, poisonAction };
State deadState = { Dead, deadAction };

Human* changeState(Human *self, State *state);

int main(void){
    Human human = { "Takeshi", &fineState, action, changeState, };

    action(&human);
    action(&human);
    action(&human);

    return 0;
}

void fineAction(Human *self) {
    printf("%s is fine!\n", self->name);
    self->changeState(self, &poisonState);
}

void poisonAction(Human *self) {
    printf("%s is poison...\n", self->name);
    self->changeState(self, &deadState);
}

void deadAction(Human *self) {
    printf("...\n");
    self->changeState(self, &fineState);
}

void action(Human *self) {
    self->state->action(self);
}

Human* changeState(Human *self, State *state) {
    self->state = state;
    return self;
}
