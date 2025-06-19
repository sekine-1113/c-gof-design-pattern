#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Recipe {
    void (*make)(struct _Recipe* self);
    void (*prepare)(struct _Recipe* self);
    void (*cook)(struct _Recipe* self);
    void (*serve)(struct _Recipe* self);
} Recipe;

void make(Recipe* self) {
    self->prepare(self);
    self->cook(self);
    self->serve(self);
}

void init_Recipe(Recipe* recipe, void (*prepare)(struct _Recipe* self), void (*cook)(struct _Recipe* self), void (*serve)(struct _Recipe* self)) {
    recipe->make = make;
    recipe->prepare = prepare;
    recipe->cook = cook;
    recipe->serve = serve;
}

typedef struct _RamenRecipe {
    Recipe base;
} RamenRecipe;

void prepareRamen(Recipe* self) {
    printf("鍋とラーメンを用意します。\n");
}

void cookRamen(Recipe* self) {
    printf("鍋でラーメンを茹でます。\n");
}

void serveRamen(Recipe* self) {
    printf("器にラーメンを盛り付けて完成！\n");
}

typedef struct _UdonRecipe {
    Recipe base;
} UdonRecipe;

void prepareUdon(Recipe* self) {
    printf("鍋とうどんを用意します。\n");
}

void cookUdon(Recipe* self) {
    printf("鍋でうどんを茹でます。\n");
}

void serveUdon(Recipe* self) {
    printf("器にうどんを盛り付けて完成！\n");
}

void makeRecipe(Recipe* recipe) {
    recipe->make(recipe);
}

int main(void) {
    RamenRecipe ramenRecipe;
    init_Recipe((Recipe*)&ramenRecipe, prepareRamen, cookRamen, serveRamen);
    UdonRecipe udonRecipe;
    init_Recipe((Recipe*)&udonRecipe, prepareUdon, cookUdon, serveUdon);

    makeRecipe((Recipe*)&ramenRecipe);
    makeRecipe((Recipe*)&udonRecipe);
    return 0;
}
