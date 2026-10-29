#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int coeff, exp;
    struct Node *next;
} Node;

/* An empty list is just a header node pointing to itself. */
Node *newList(void)
{
    Node *head = malloc(sizeof(Node));

    if (head == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    head->coeff = 0;
    head->exp = 0;
    head->next = head;
    return head;
}

/* Insert in descending exponent order, combining equal exponents. */
void insert(Node *head, int c, int e)
{
    if (c == 0)
        return;

    Node *prev = head, *cur = head->next;

    while (cur != head && cur->exp > e)
    {
        prev = cur;
        cur = cur->next;
    }

    if (cur != head && cur->exp == e)
    {
        cur->coeff += c;

        if (cur->coeff == 0)
        {
            prev->next = cur->next;
            free(cur);
        }
        return;
    }

    Node *n = malloc(sizeof(Node));

    if (n == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    n->coeff = c;
    n->exp = e;
    n->next = cur;
    prev->next = n;
}

void create(Node *head)
{
    int n, c, e;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter coefficient and exponent: ");
        scanf("%d%d", &c, &e);
        insert(head, c, e);
    }
}

void display(Node *head)
{
    Node *p = head->next;

    if (p == head)
    {
        printf("0\n");
        return;
    }

    int first = 1;

    while (p != head)
    {
        if (!first)
        {
            if (p->coeff > 0)
                printf(" + ");
            else
                printf(" - ");
        }
        else if (p->coeff < 0)
        {
            printf("-");
        }

        int c = abs(p->coeff);

        if (p->exp == 0 || c != 1)
            printf("%d", c);

        if (p->exp > 0)
        {
            printf("x");

            if (p->exp > 1)
                printf("^%d", p->exp);
        }

        first = 0;
        p = p->next;
    }

    printf("\n");
}

Node *add(Node *a, Node *b)
{
    Node *sum = newList();
    Node *p;

    for (p = a->next; p != a; p = p->next)
        insert(sum, p->coeff, p->exp);

    for (p = b->next; p != b; p = p->next)
        insert(sum, p->coeff, p->exp);

    return sum;
}

void freeList(Node *head)
{
    Node *p = head->next;

    while (p != head)
    {
        Node *temp = p;
        p = p->next;
        free(temp);
    }

    free(head);
}

int main(void)
{
    Node *p1 = newList();
    Node *p2 = newList();

    printf("Polynomial 1\n");
    create(p1);

    printf("Polynomial 2\n");
    create(p2);

    printf("P1 = ");
    display(p1);
    printf("P2 = ");
    display(p2);

    Node *sum = add(p1, p2);

    printf("Sum = ");
    display(sum);

    freeList(p1);
    freeList(p2);
    freeList(sum);

    return 0;
}
