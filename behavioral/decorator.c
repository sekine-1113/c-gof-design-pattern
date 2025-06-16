#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Decorator {
    struct _Decorator* component;
    char decorate_char;
    char* (*decorate)(struct _Decorator* self, char* str);
} Decorator;
char* decorate(Decorator* self, char* str);

Decorator* new_Decorator(char c, Decorator* decorator) {
    Decorator* deco = (Decorator*)malloc(sizeof(Decorator));
    deco->component = decorator;
    deco->decorate_char = c;
    deco->decorate = decorate;
    return deco;
}

void delete_Decorator(Decorator* decorator) {
    if (decorator->component != NULL) {
        delete_Decorator(decorator->component);
    }
    free(decorator);
}

int main(void) {
    char *str = "Hello";
    Decorator* deco = new_Decorator('\'', new_Decorator('*', new_Decorator('+', new_Decorator('.', NULL))));
    char *result = deco->decorate(deco, str);
    printf("%s\n", result);

    free(result);
    delete_Decorator(deco);
    return 0;
}

char* decorate(Decorator* self, char* str) {
    char* base_str;

    if (self->component != NULL) {
        base_str = self->component->decorate(self->component, str);
    } else {
        base_str = strdup(str);
    }

    char* new_str = (char*)malloc(strlen(base_str) + 3);
    sprintf(new_str, "%c%s%c", self->decorate_char, base_str, self->decorate_char);
    free(base_str);
    return new_str;
}
