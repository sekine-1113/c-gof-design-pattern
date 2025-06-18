#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _MainDish {
    void (*serve)(struct _MainDish* self);
} MainDish;

typedef struct _Rice {
    MainDish base;
} Rice;

void serveRice(struct _MainDish* self) {
    printf("・ごはん\n");
}

MainDish* createRice(void) {
    Rice* rice = (Rice*)malloc(sizeof(Rice));
    rice->base.serve = serveRice;
    return (MainDish*)rice;
}

typedef struct _Hamburger {
    MainDish base;
} Hamburger;

void serveHamburger(struct _MainDish* self) {
    printf("・ハンバーガー\n");
}

MainDish* createHamburger(void) {
    Hamburger* hamburger = (Hamburger*)malloc(sizeof(Hamburger));
    hamburger->base.serve = serveHamburger;
    return (MainDish*)hamburger;
}

typedef struct _Drink {
    void (*serve)(struct _Drink* self);
} Drink;

typedef struct _GreenTea {
    Drink base;
} GreenTea;

void serveGreenTea(Drink* self) {
    printf("・緑茶\n");
}

Drink* createGreenTea(void) {
    GreenTea* greenTea = (GreenTea*)malloc(sizeof(GreenTea));
    greenTea->base.serve = serveGreenTea;
    return (Drink*)greenTea;
}

typedef struct _Coke {
    Drink base;
} Coke;

void serveCoke(Drink* self) {
    printf("・コーラ\n");
}

Drink* createCoke(void) {
    Coke* coke = (Coke*)malloc(sizeof(Coke));
    coke->base.serve = serveCoke;
    return (Drink*)coke;
}

typedef struct _MenuFactory {
    MainDish* (*createMainDish)(void);
    Drink* (*createDrink)(void);
} MenuFactory;

MenuFactory createJapaneseMenuFactory(void) {
    MenuFactory menuFactory;
    menuFactory.createMainDish = createRice;
    menuFactory.createDrink = createGreenTea;
    return menuFactory;
}

MenuFactory createAmericanMenuFactory(void) {
    MenuFactory menuFactory;
    menuFactory.createMainDish = createHamburger;
    menuFactory.createDrink = createCoke;
    return menuFactory;
}

void serveMenu(MenuFactory menu) {
    MainDish* mainDish = menu.createMainDish();
    Drink* drink = menu.createDrink();
    mainDish->serve(mainDish);
    drink->serve(drink);
    free(mainDish);
    free(drink);
}

int main(void) {
    MenuFactory japaneseMenuFactory = createJapaneseMenuFactory();
    MenuFactory americanMenuFactory = createAmericanMenuFactory();
    printf("<Japanese Menu>\n");
    serveMenu(japaneseMenuFactory);
    printf("<American Menu>\n");
    serveMenu(americanMenuFactory);
    return 0;
}
