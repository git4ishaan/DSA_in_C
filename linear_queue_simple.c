#include <stdio.h>

#define MAX 5

int queue[MAX];
int front = -1, rear = -1;

/* Add an item at the rear */
void enqueue()
{
    int value;

    if (rear == MAX - 1)
    {
        printf("Queue Overflow!\n");
        return;
    }

    printf("Enter value: ");
    scanf("%d", &value);

    if (front == -1)          /* first item */
        front = 0;

    rear++;
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
    front++;

    if (front > rear)         /* last item removed */
    {
        front = -1;
        rear = -1;
    }
}

/* Print items from front to rear */
void display()
{
    int i;

    if (front == -1)
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue: ");
    for (i = front; i <= rear; i++)
        printf("%d ", queue[i]);
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
