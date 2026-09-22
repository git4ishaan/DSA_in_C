#include <stdio.h>
#include <string.h>

#define MAX 5

struct Job {
    int id;
    char title[50];
};

struct Job queue[MAX];
int front = -1, rear = -1;

/* Enqueue */
void enqueue() {
    struct Job job;

    if ((rear + 1) % MAX == front) {
        printf("Queue Overflow! Print queue is full.\n");
        return;
    }

    printf("Enter Job ID: ");
    scanf("%d", &job.id);

    printf("Enter Document Title: ");
    scanf(" %[^\n]", job.title);

    if (front == -1) {
        front = 0;
        rear = 0;
    } else {
        rear = (rear + 1) % MAX;
    }

    queue[rear] = job;

    printf("Print job is added successfully to the queue.\n");
}

/* Dequeue */
void dequeue() {
    if (front == -1) {
        printf("Queue Underflow! No print jobs available.\n");
        return;
    }

    printf("\nProcessed Print Job:\n");
    printf("Job ID: %d\n", queue[front].id);
    printf("Document Title: %s\n", queue[front].title);

    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % MAX;
    }
}

/* Display */
void display() {
    int i;

    if (front == -1) {
        printf("Queue is empty.\n");
        return;
    }

    printf("\nPending Print Jobs:\n");

    i = front;

    while (1) {
        printf("Job ID: %d | Document: %s\n",
               queue[i].id, queue[i].title);

        if (i == rear)
            break;

        i = (i + 1) % MAX;
    }
}

/* Main */
int main() {
    int choice;

    do {
        printf("\n===== CIRCULAR PRINTER QUEUE =====\n");
        printf("1. Enqueue Print Job\n");
        printf("2. Dequeue Print Job\n");
        printf("3. Display All Jobs\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
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
                printf("Program terminated successfully.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}