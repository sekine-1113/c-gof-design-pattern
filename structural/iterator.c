#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define new_Iterable(type, max_length) _new_Iterable(sizeof(type), max_length)
#define add_Iterable(iter, value) _add_Iterable(iter, &(value))
#define next(type, iter) *(type*)_next(iter)
#define N 10


typedef struct _Iterable {
    void* array;
    size_t element_size;
    size_t length;
    size_t maxLength;
    size_t cursor;
    int (*hasNext)(struct _Iterable* self);
} Iterable;

int hasNext(Iterable* self) {
    return self->cursor < self->length;
}

Iterable* _new_Iterable(size_t element_size, size_t max_length) {
    Iterable* iter = (Iterable*)malloc(sizeof(Iterable));
    iter->element_size = element_size;
    iter->array = malloc(iter->element_size * max_length);
    iter->length = 0;
    iter->maxLength = max_length;
    iter->cursor = 0;
    iter->hasNext = hasNext;
    return iter;
}

void delete_Iterable(Iterable* iter) {
    free(iter->array);
    free(iter);
}

void set_Iterable(Iterable* iter, void* values, size_t length) {
    memcpy(iter->array, values, iter->element_size * length);
    iter->length = length;
}

void _add_Iterable(Iterable* iter, void* value) {
    if (iter->length + 1 < iter->maxLength) {
        void* target = iter->array + iter->element_size * iter->length;
        memcpy(target, value, iter->element_size);
        iter->length++;
    }
}

void* _next(Iterable* iter) {
    void* ptr = iter->array + (iter->element_size * iter->cursor);
    iter->cursor++;
    return ptr;
}

int main(void){
    Iterable* it = new_Iterable(int, N*2);
    int values[N] = {0};
    for (int i=0; i<N; i++) {
        int tmp = rand() % 1024;
        add_Iterable(it, tmp);
    };

    while (it->hasNext(it)) {
        printf("%d\n", next(int, it));
    }

    delete_Iterable(it);

    it = new_Iterable(char*, N);
    char* strings[2] = {"Hello", "World"};
    set_Iterable(it, strings, 2);

    while (it->hasNext(it)) {
        printf("%s\n", next(char*, it));
    }

    delete_Iterable(it);
    return 0;
}
