#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HISTORY_SIZE 8

typedef struct _Command {
    void (*execute)(struct _Command* self);
    void (*undo)(struct _Command* self);
} Command;

typedef struct _LightOnCommand {
    Command base;
} LightOnCommand;
void executeLightOn(struct _Command* self);
void undoLightOn(struct _Command* self);

typedef struct _LightDimCommand {
    Command base;
} LightDimCommand;
void executeLightDim(struct _Command* self);
void undoLightDim(struct _Command* self);

typedef struct _LightOffCommand {
    Command base;
} LightOffCommand;
void executeLightOff(struct _Command* self);
void undoLightOff(struct _Command* self);

typedef struct _RemoteControler {
    Command* currentCommand;
    Command* history[HISTORY_SIZE];
    unsigned int historyLength;
    unsigned int historyIndex;
    void (*setCommand)(struct _RemoteControler* self, Command* command);
    void (*pressButton)(struct _RemoteControler* self);
    void (*undo)(struct _RemoteControler* self);
    void (*redo)(struct _RemoteControler* self);
} RemoteControler;
void setCommand(RemoteControler* self, Command* command);
void pressButton(RemoteControler* self);
void undo(RemoteControler* self);
void redo(RemoteControler* self);
RemoteControler* new_RemoteControler(Command* command);
void delete_RemoteControler(RemoteControler* remote);

int main(void) {
    LightOnCommand lightOnCommand = { { executeLightOn, undoLightOn } };
    LightDimCommand lightDimCommand = { { executeLightDim, undoLightDim } };
    LightOffCommand lightOffCommand = { { executeLightOff, undoLightOff } };
    RemoteControler* remote = new_RemoteControler((Command*)&lightOnCommand);
    remote->pressButton(remote);

    remote->setCommand(remote, (Command*)&lightDimCommand);
    remote->pressButton(remote);

    remote->setCommand(remote, (Command*)&lightOffCommand);
    remote->pressButton(remote);

    remote->undo(remote);
    remote->undo(remote);
    remote->undo(remote);

    remote->redo(remote);
    remote->redo(remote);
    remote->redo(remote);

    delete_RemoteControler(remote);
    return 0;
}

void executeLightOn(struct _Command* self) {
    printf("Light ON\n");
}

void undoLightOn(struct _Command* self) {
    printf("UNDO: Light ON\n");
}

void executeLightDim(struct _Command* self) {
    printf("Light DIM\n");
}

void undoLightDim(struct _Command* self) {
    printf("UNDO: Light DIM\n");
}

void executeLightOff(struct _Command* self) {
    printf("Light OFF\n");
}

void undoLightOff(struct _Command* self) {
    printf("UNDO: Light Off\n");
}

void setCommand(RemoteControler* self, Command* command) {
    self->currentCommand = command;
}

void pressButton(RemoteControler* self) {
    // UNDO されていたら履歴更新
    if (self->historyIndex + 1 < self->historyLength) {
        self->historyLength = self->historyIndex + 1;
    }

    if (self->historyLength < HISTORY_SIZE) {
        self->historyIndex++;
        self->history[self->historyIndex] = self->currentCommand;
        self->historyLength = self->historyIndex + 1;
        self->history[self->historyIndex]->execute(self->history[self->historyIndex]);
    }
}

void undo(RemoteControler* self) {
    if (self->historyIndex != -1) {
        self->history[self->historyIndex]->undo(self->history[self->historyIndex]);
        self->historyIndex--;
    } else {
        printf("Nothing to undo\n");
    }
}

void redo(RemoteControler* self) {
    if (self->historyIndex + 1 < self->historyLength) {
        printf("REDO: ");
        self->historyIndex++;
        self->history[self->historyIndex]->execute(self->history[self->historyIndex]);
    } else {
        printf("Nothing to redo\n");
    }
}

RemoteControler* new_RemoteControler(Command* command) {
    RemoteControler* self = (RemoteControler*)malloc(sizeof(RemoteControler));
    self->currentCommand = command;
    self->historyLength = 0;
    self->historyIndex = -1;
    self->setCommand = setCommand;
    self->pressButton = pressButton;
    self->undo = undo;
    self->redo = redo;
    return self;
}

void delete_RemoteControler(RemoteControler* remote) {
    free(remote);
}
