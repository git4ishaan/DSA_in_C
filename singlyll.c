
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int regNo;
    char name[50];
    struct Student *next;
};

struct Student *head = NULL;

void addStudent()
{
    struct Student *newNode, *temp;
    newNode = (struct Student *)malloc(sizeof(struct Student));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter Registration Number: ");
    scanf("%d", &newNode->regNo);
    printf("Enter Name: ");
    scanf(" %49[^\n]", newNode->name);
    newNode->next = NULL;

    if (head == NULL)
        head = newNode;
    else
    {
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    printf("Student added successfully.\n");
}

void removeStudent()
{
    struct Student *temp = head, *prev = NULL;
    int reg;

    printf("Enter Registration Number to remove: ");
    scanf("%d", &reg);

    while (temp != NULL && temp->regNo != reg)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Student not found.\n");
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("Student removed successfully.\n");
}

void display()
{
    struct Student *temp = head;

    if (head == NULL)
    {
        printf("No students registered.\n");
        return;
    }

    printf("\nRegistration No.\tName\n");
    while (temp != NULL)
    {
        printf("%d\t\t\t%s\n", temp->regNo, temp->name);
        temp = temp->next;
    }
}

void countStudents()
{
    struct Student *temp = head;
    int count = 0;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    printf("Total participants: %d\n", count);
}

void sortStudents()
{
    struct Student *i, *j;
    int reg;
    char name[50];

    for (i = head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->regNo > j->regNo)
            {
                reg = i->regNo;
                i->regNo = j->regNo;
                j->regNo = reg;

                strcpy(name, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, name);
            }
        }
    }

    printf("List sorted by Registration Number.\n");
}

void reverseList()
{
    struct Student *prev = NULL, *current = head, *next;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;
    printf("List reversed successfully.\n");
}

int main()
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
        struct Student *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
