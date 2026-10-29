#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
    int regNo;
    char name[50];
    struct Student *next;
} Student;

Student *head = NULL;

void addStudent(void)
{
    Student *s = malloc(sizeof(Student));

    if (s == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter Registration Number: ");
    scanf("%d", &s->regNo);
    printf("Enter Name: ");
    scanf(" %49[^\n]", s->name);
    s->next = NULL;

    if (head == NULL)
    {
        head = s;
    }
    else
    {
        Student *p = head;
        while (p->next != NULL)
            p = p->next;
        p->next = s;
    }

    printf("Student added successfully.\n");
}

void removeStudent(void)
{
    int reg;

    printf("Enter Registration Number to remove: ");
    scanf("%d", &reg);

    Student *cur = head, *prev = NULL;

    while (cur != NULL && cur->regNo != reg)
    {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL)
    {
        printf("Student not found.\n");
        return;
    }

    if (prev == NULL)
        head = cur->next;
    else
        prev->next = cur->next;

    free(cur);
    printf("Student removed successfully.\n");
}

void display(void)
{
    if (head == NULL)
    {
        printf("No students registered.\n");
        return;
    }

    printf("\nRegistration No.\tName\n");

    for (Student *p = head; p != NULL; p = p->next)
        printf("%d\t\t\t%s\n", p->regNo, p->name);
}

void countStudents(void)
{
    int count = 0;

    for (Student *p = head; p != NULL; p = p->next)
        count++;

    printf("Total participants: %d\n", count);
}

/* Swaps only the data, not the next pointers. */
void swapData(Student *a, Student *b)
{
    int reg = a->regNo;
    a->regNo = b->regNo;
    b->regNo = reg;

    char name[50];
    strcpy(name, a->name);
    strcpy(a->name, b->name);
    strcpy(b->name, name);
}

void sortStudents(void)
{
    for (Student *i = head; i != NULL; i = i->next)
    {
        for (Student *j = i->next; j != NULL; j = j->next)
        {
            if (i->regNo > j->regNo)
                swapData(i, j);
        }
    }

    printf("List sorted by Registration Number.\n");
}

void reverseList(void)
{
    Student *prev = NULL, *cur = head, *next;

    while (cur != NULL)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    head = prev;
    printf("List reversed successfully.\n");
}

int main(void)
{
    int choice;

    do
    {
        printf("\n--- Workshop Enrollment System ---\n");
        printf("1. Add Student\n");
        printf("2. Remove Student\n");
        printf("3. Display Students\n");
        printf("4. Count Participants\n");
        printf("5. Sort Students\n");
        printf("6. Reverse List\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            removeStudent();
            break;
        case 3:
            display();
            break;
        case 4:
            countStudents();
            break;
        case 5:
            sortStudents();
            break;
        case 6:
            reverseList();
            break;
        case 0:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);

    while (head != NULL)
    {
        Student *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
