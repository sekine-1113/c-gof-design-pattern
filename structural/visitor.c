#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person Person;
typedef struct _Student Student;
typedef struct _Older Older;
typedef struct _Younger Younger;

typedef struct _Visitor {
    void (*visitStudent)(struct _Visitor* self, Student* student);
    void (*visitOlder)(struct _Visitor* self, Older* older);
    void (*visitYounger)(struct _Visitor* self, Younger* younger);
    char* name;
} Visitor;

typedef struct _Person {
    void (*accept)(struct _Person* self, struct _Visitor* visitor);
} Person;

typedef struct _Student {
    Person base;
    char* name;
} Student;
typedef struct _Older {
    Person base;
    char* name;
} Older;
typedef struct _Younger {
    Person base;
    char* name;
} Younger;

void visitStudent(struct _Visitor* self, Student* student);
void visitOlder(struct _Visitor* self, Older* older);
void visitYounger(struct _Visitor* self, Younger* younger);

void acceptStudent(struct _Person* self, struct _Visitor* visitor);
void acceptOlder(struct _Person* self, struct _Visitor* visitor);
void acceptYounger(struct _Person* self, struct _Visitor* visitor);


int main(void) {
    Visitor doctor = { visitStudent, visitOlder, visitYounger, "お医者さん" };
    Student student = { { acceptStudent }, "学生" };
    Older older = { { acceptOlder }, "高齢者" };
    Younger younger = { { acceptYounger }, "若者" };

    student.base.accept((Person*)&student, &doctor);
    older.base.accept((Person*)&older, &doctor);
    younger.base.accept((Person*)&younger, &doctor);

    return 0;
}

void visitStudent(struct _Visitor* self, Student* student) {
    printf("%s は %s の健康診断をした\n", self->name, student->name);
}
void visitOlder(struct _Visitor* self, Older* older) {
    printf("%s は %s の血圧を測定した\n", self->name, older->name);
}
void visitYounger(struct _Visitor* self, Younger* younger) {
    printf("%s は %s の身体検査をした\n", self->name, younger->name);
}

void acceptStudent(struct _Person* self, struct _Visitor* visitor) {
    visitor->visitStudent(visitor, (Student*)self);
}
void acceptOlder(struct _Person* self, struct _Visitor* visitor) {
    visitor->visitOlder(visitor, (Older*)self);
}
void acceptYounger(struct _Person* self, struct _Visitor* visitor) {
    visitor->visitYounger(visitor, (Younger*)self);
}
