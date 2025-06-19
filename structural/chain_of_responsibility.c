#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Employee {
    struct _Employee* next;
    void (*setNext)(struct _Employee* self, struct _Employee* next);
    void (*approveRequest)(struct _Employee* self, int amount);
} Employee;
void setNext(struct _Employee* self, struct _Employee* next) {
    self->next = next;
}
void delete_Employee(Employee* employee) {
    if (employee == NULL) return;
    if (employee->next != NULL) {
        delete_Employee(employee->next);
    }
    free(employee);
}

typedef struct _Staff {
    Employee base;
} Staff;
void approveRequestByStaff(Employee* self, int amount);
Employee* new_Staff(Employee* next);

typedef struct _Manager {
    Employee base;
} Manager;
void approveRequestByManager(Employee* self, int amount);
Employee* new_Manager(Employee* next);

typedef struct _President {
    Employee base;
} President;
void approveRequestByPresident(Employee* self, int amount);
Employee* new_President(void);


int main(void){
    Employee *president = new_President();
    Employee *manager = new_Manager(president);
    Employee *staffA = new_Staff(manager);
    Employee *staffB = new_Staff(NULL);

    staffA->approveRequest(staffA, 3000);
    staffA->approveRequest(staffA, 300000);
    staffA->approveRequest(staffA, 30000000);

    staffB->approveRequest(staffB, 100000);

    delete_Employee(staffA);
    delete_Employee(staffB);
}

void approveRequestByStaff(Employee* self, int amount) {
    printf("Request Recieved(Staff): %d -> ", amount);
    if (amount <= 50000) {
        printf("Staff Approved.\n");
    } else if (self->next != NULL) {
        printf("Approve Request to Manager from Staff -> ");
        self->next->approveRequest(self->next, amount);
    } else {
        printf("No one can approve this request.\n");
    }
}

Employee* new_Staff(Employee* next) {
    Staff* staff = (Staff*)malloc(sizeof(Staff));
    staff->base.approveRequest = approveRequestByStaff;
    staff->base.next = next;
    staff->base.setNext = setNext;
    return (Employee*)staff;
}

void approveRequestByManager(Employee* self, int amount) {
    printf("Request Recieved(Manager): %d -> ", amount);
    if (amount <= 500000) {
        printf("Manager Approved.\n");
    } else if (self->next != NULL) {
        printf("Approve Request to President from Manager -> ");
        self->next->approveRequest(self->next, amount);
    } else {
        printf("No one can approve this request.\n");
    }
}

Employee* new_Manager(Employee* next) {
    Manager* manager = (Manager*)malloc(sizeof(Manager));
    manager->base.approveRequest = approveRequestByManager;
    manager->base.next = next;
    manager->base.setNext = setNext;
    return (Employee*)manager;
}

void approveRequestByPresident(Employee* self, int amount) {
    printf("Request Recieved(President): %d -> ", amount);
    printf("President Approved.\n");
}

Employee* new_President(void) {
    President* president = (President*)malloc(sizeof(President));
    president->base.approveRequest = approveRequestByPresident;
    president->base.next = NULL;
    president->base.setNext = setNext;
    return (Employee*)president;
}
