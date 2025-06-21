#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Actor Actor;
typedef struct _Weapon {
    void (*apply)(struct _Weapon* self, struct _Actor* actor);
} Weapon;

typedef struct _Actor {
    char* name;
    Weapon* weapon;
    void (*equipWeapon)(struct _Actor* self, Weapon* weapon);
} Actor;

typedef struct _Warrior {
    Actor base;
} Warrior;

typedef struct _Mage {
    Actor base;
} Mage;

void applySword(struct _Weapon* self, struct _Actor* actor) ;
void applyWand(struct _Weapon* self, struct _Actor* actor);
void equipWeapon(struct _Actor* self, Weapon* weapon);

int main(void) {
    Weapon sword = { applySword };
    Weapon wand = { applyWand };
    Warrior warrior = { { "Alice", NULL, equipWeapon } };
    Mage mage = { { "Bob", NULL, equipWeapon } };

    warrior.base.equipWeapon((Actor*)&warrior, &sword);
    mage.base.equipWeapon((Actor*)&mage, &wand);

    return 0;
}

void applySword(struct _Weapon* self, struct _Actor* actor) {
    printf("%s は剣を装備した\n", actor->name);
    actor->weapon = self;
}

void applyWand(struct _Weapon* self, struct _Actor* actor) {
    printf("%s は杖を装備した\n", actor->name);
    actor->weapon = self;
}

void equipWeapon(struct _Actor* self, Weapon* weapon) {
    weapon->apply(weapon, self);
}
