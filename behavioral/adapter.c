#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Animal {
    void (*makeSound)(struct _Animal* self);
} Animal;

typedef struct _Lion {
    Animal base;
    void (*bark)(struct _Lion* self);
} Lion;

typedef struct _Cat {
    Animal base;
    void (*meow)(struct _Cat* self);
} Cat;

typedef struct _Dog {
    Animal base;
    void (*baw)(struct _Dog* self);
} Dog;

void bark(struct _Lion* self);
void meow(struct _Cat* self);
void baw(struct _Dog* self);
void makeSoundLion(struct _Animal* self);
void makeSoundCat(struct _Animal* self);
void makeSoundDog(struct _Animal* self);
void makeSound(struct _Animal* animal);

int main(void) {
    Lion lion = { { makeSoundLion }, bark };
    Cat cat = { { makeSoundCat }, meow };
    Dog dog = { { makeSoundDog }, baw };
    Animal* animals[3] = {
        (Animal*)&lion,
        (Animal*)&cat,
        (Animal*)&dog
    };
    for (int i=0; i<3; i++) {
        animals[i]->makeSound(animals[i]);
    }
    return 0;
}

void bark(struct _Lion* self) {
    printf("Bark\n");
}

void meow(struct _Cat* self) {
    printf("Meow\n");
}

void baw(struct _Dog* self) {
    printf("Baw\n");
}

void makeSoundLion(struct _Animal* self) {
    ((Lion*)self)->bark((Lion*)self);
}

void makeSoundCat(struct _Animal* self) {
    ((Cat*)self)->meow((Cat*)self);
}

void makeSoundDog(struct _Animal* self) {
    ((Dog*)self)->baw((Dog*)self);
}

void makeSound(struct _Animal* animal) {
    animal->makeSound(animal);
}
