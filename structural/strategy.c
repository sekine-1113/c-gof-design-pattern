#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3

typedef enum _JobType {
    Wizard,
    Fighter,
    Healer,
} JobType;

typedef struct _Strategy {
    void (*action)(void);
} Strategy;
void magic(void) { printf("魔法攻撃!\n"); }
void punch(void) { printf("パンチ攻撃!\n"); }
void heal(void) { printf("回復!\n"); }
static Strategy wizardStrategy = { magic };
static Strategy fighterStrategy = { punch };
static Strategy healerStrategy = { heal };

typedef struct _Player {
    char* name;
    void (*action)(const struct _Player* self);
    Strategy* strategy;
} Player;
Player* new_Player(JobType job, char* name);
void delete_Player(Player* player);
void action(const Player *self);

int main(void){
    Player* players[N];
    players[0] = new_Player(Wizard, "魔法使い");
    players[1] = new_Player(Fighter, "ファイター");
    players[2] = new_Player(Healer, "ヒーラー");

    for (int i=0; i<N; i++) {
        if (players[i] == NULL) exit(1);
        players[i]->action(players[i]);
        delete_Player(players[i]);
    }

    return 0;
}

void action(const Player *self) {
    printf("%sの行動: ", self->name);
    self->strategy->action();
}

Player* new_Player(JobType job, char* name) {
    Player* player = (Player*)malloc(sizeof(Player));
    player->name = strdup(name);
    player->action = action;
    switch (job) {
        case Wizard:
            player->strategy = &wizardStrategy;
            break;
        case Fighter:
            player->strategy = &fighterStrategy;
            break;
        case Healer:
            player->strategy = &healerStrategy;
            break;
        default:
            free(player->name);
            free(player);
            return NULL;
    }
    return player;
}

void delete_Player(Player* player) {
    free(player->name);
    free(player);
}
