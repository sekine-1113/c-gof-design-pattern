#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Operation Operation;
typedef void (*DoOperationFunc)(struct _Operation*);

typedef struct _Operation {
    DoOperationFunc doOperation;
} Operation;

typedef struct _Operator {
    void (*operate)(struct _Operator* self);
    Operation operationA;
    Operation operationB;
    Operation operationC;
} Operator;
void doOperationA(struct _Operation* self);
void doOperationB(struct _Operation* self);
void doOperationC(struct _Operation* self);
void operate(Operator* self);
Operator* new_Operator(DoOperationFunc func1, DoOperationFunc func2, DoOperationFunc func3);

int main(void) {
    Operator* operator = new_Operator(doOperationA, doOperationB, doOperationC);

    operator->operate(operator);

    return 0;
}

void doOperationA(struct _Operation* self) {
    printf("オペレーションAを実行！\n");
}

void doOperationB(struct _Operation* self) {
    printf("オペレーションBを実行！\n");
}

void doOperationC(struct _Operation* self) {
    printf("オペレーションCを実行！\n");
}

void operate(Operator* self) {
    self->operationA.doOperation(&self->operationA);
    self->operationB.doOperation(&self->operationB);
    self->operationC.doOperation(&self->operationC);
}

Operator* new_Operator(DoOperationFunc func1, DoOperationFunc func2, DoOperationFunc func3) {
    Operator* operator = (Operator*)malloc(sizeof(Operator));
    operator->operate = operate;
    operator->operationA = (Operation){ func1 };
    operator->operationB = (Operation){ func2 };
    operator->operationC = (Operation){ func3 };
    return operator;
}
