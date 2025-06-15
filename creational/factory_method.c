#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _Product {
    char* name;
    void (*print_name)(struct _Product* self);
} Product;
void print_name(struct _Product* self) {
    printf("%s\n", self->name);
}
static Product PS5 = { "PS5", print_name };
static Product Switch2 = { "Switch2", print_name };


typedef struct _Factory {
    Product* (*create_product)(void);
} Factory;
Product* create_ps5(void) {
    Product *product = &PS5;
    return product;
}
Product* create_switch2(void) {
    Product *product = &Switch2;
    return product;
}
Factory PS5Factory = { create_ps5 };
Factory Switch2Factory = { create_switch2 };


int main(void) {
    Factory factories[2] = {
        PS5Factory, Switch2Factory,
    };
    for (int i=0; i<2; i++) {
        Product* product = factories[i].create_product();
        product->print_name(product);
    }
    return 0;
}
