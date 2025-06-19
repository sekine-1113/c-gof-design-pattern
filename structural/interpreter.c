#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Expression {
    int _number;
    struct _Expression* left;
    struct _Expression* right;
    int (*interpret)(struct _Expression* self);
} Expression;

typedef struct _Number {
    Expression base;
} Number;

int interpretNumber(struct _Expression* self) {
    return self->_number;
}
Number* new_Number(int number) {
    Number* self = (Number*)malloc(sizeof(Number));
    self->base = (Expression){ number, NULL, NULL, interpretNumber};
    return self;
}

typedef struct _Add {
    Expression base;
} Add;
int interpretAdd(struct _Expression* self) {
    if (self->left == NULL || self->right == NULL) return 0;
    self->_number = self->left->interpret(self->left) + self->right->interpret(self->right);
    return self->_number;
}
Add* new_Add(Expression* left, Expression* right) {
    Add* self = (Add*)malloc(sizeof(Add));
    self->base = (Expression){ 0, left, right, interpretAdd };
    return self;
}

typedef struct _Subtract {
    Expression base;
} Subtract;
int interpretSubtract(struct _Expression* self) {
    if (self->left == NULL || self->right == NULL) return 0;
    self->_number = self->left->interpret(self->left) - self->right->interpret(self->right);
    return self->_number;
}
Subtract* new_Subtract(Expression* left, Expression* right) {
    Subtract* self = (Subtract*)malloc(sizeof(Subtract));
    self->base = (Expression){ 0, left, right, interpretSubtract };
    return self;
}

void delete_Expression(Expression* expression) {
    if (expression == NULL) return;
    if (expression->left != NULL) {
        delete_Expression(expression->left);
    }
    if (expression->right != NULL) {
        delete_Expression(expression->right);
    }
    free(expression);
}

void printExpression(Expression* self) {
    if (self->left != NULL) printExpression(self->left);
    if (self->interpret == interpretAdd) printf(" + ");
    else if (self->interpret == interpretSubtract) printf(" - ");
    else printf("%d", self->_number);
    if (self->right != NULL) printExpression(self->right);
}

int main(void) {
    Expression* expression = (Expression*)new_Subtract(
        (Expression*)new_Add((Expression*)new_Number(10), (Expression*)new_Number(6)),
        (Expression*)new_Number(8)
    );

    printExpression(expression);

    int result = expression->interpret(expression);
    printf(" = %d\n", result);
    delete_Expression(expression);
    return 0;
}
