#include <stdio.h>

#define MAX 5

int queue[MAX];
int front = -1, rear = -1;

/* Add an item at the rear (wraps around) */
void enqueue()
{
    int value;

    if ((rear + 1) % MAX == front)
    {
        printf("Queue Overflow!\n");
        return;
    }

    printf("Enter value: ");
    scanf("%d", &value);

    if (front == -1)          /* first item */
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = (rear + 1) % MAX;
    }

    queue[rear] = value;
    printf("%d inserted.\n", value);
}

/* Remove the item at the front */
void dequeue()
{
    if (front == -1)
    {
        printf("Queue Underflow!\n");
        return;
    }

    printf("Deleted: %d\n", queue[front]);

    if (front == rear)        /* last item removed */
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % MAX;
    }
}

/* Print items from front to rear, wrapping around */
void display()
{
    int i;

    if (front == -1)
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue: ");
    i = front;

    while (1)
    {
        printf("%d ", queue[i]);

        if (i == rear)
            break;

        i = (i + 1) % MAX;
    }

    printf("\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n1.Insert  2.Delete  3.Display  4.Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: enqueue(); break;
        case 2: dequeue(); break;
        case 3: display(); break;
        case 4: printf("Bye.\n"); break;
        default: printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
