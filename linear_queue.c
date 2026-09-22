#include <stdio.h>
#include <string.h>

#define MAX 5

struct Job
{
    int id;
    char title[50];
};

struct Job queue[MAX];
int front = -1, rear = -1;

/* Enqueue */
void enqueue()
{
    struct Job job;

    if (rear == MAX - 1)
    {
        printf("Queue Overflow! Queue is full.\n");
        return;
    }

    printf("Enter Job ID: ");
    scanf("%d", &job.id);

    printf("Enter Document Title: ");
    scanf(" %[^\n]", job.title);

    if (front == -1)
        front = 0;

    rear++;
    queue[rear] = job;

    printf("Job inserted successfully.\n");
}

/* Dequeue */
void dequeue()
{
    if (front == -1 || front > rear)
    {
        printf("Queue Underflow! Queue is empty.\n");
        return;
    }

    printf("\nProcessing Job:\n");
    printf("Job ID: %d\n", queue[front].id);
    printf("Document: %s\n", queue[front].title);

    front++;

    /* Reset queue when it becomes empty */
    if (front > rear)
    {
        front = -1;
        rear = -1;
    }
}

/* Display */
void display()
{
    int i;

    if (front == -1)
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("\nPending Print Jobs:\n");

    for (i = front; i <= rear; i++)
    {
        printf("Job ID: %d | Document: %s\n",
               queue[i].id, queue[i].title);
    }
}

/* Main function */
int main()
{
    int choice;

    do
    {
        printf("\n===== LINEAR QUEUE =====\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            enqueue();
            break;

        case 2:
            dequeue();
            break;

        case 3:
            display();
            break;

        case 4:
            printf("Program terminated.\n");
            break;

        default:
            printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}