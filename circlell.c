
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int coeff, exp;
    struct Node *next;
};

struct Node *createNode(int c, int e)
{
    struct Node *n = malloc(sizeof(struct Node));
    if (n == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    n->coeff = c;
    n->exp = e;
    n->next = n;
    return n;
}

void insert(struct Node **head, int c, int e)
{
    if (c == 0)
        return;

    struct Node *p = *head, *prev = NULL;

    if (p != NULL)
    {
        do
        {
            if (p->exp == e)
            {
                p->coeff += c;
                if (p->coeff == 0)
                {
                    if (p->next == p)
                    {
                        *head = NULL;
                    }
                    else
                    {
                        if (prev == NULL)
                        {
                            struct Node *last = p;
                            while (last->next != p)
                                last = last->next;
                            *head = p->next;
                            last->next = *head;
                        }
                        else
                        {
                            prev->next = p->next;
                        }
                    }
                    free(p);
                }
                return;
            }
            if (p->exp < e)
                break;
            prev = p;
            p = p->next;
        } while (p != *head);
    }

    struct Node *n = createNode(c, e);

    if (*head == NULL)
    {
        *head = n;
    }
    else if (p == *head && prev == NULL)
    {
        struct Node *last = *head;
        while (last->next != *head)
            last = last->next;
        n->next = *head;
        last->next = n;
        *head = n;
    }
    else
    {
        n->next = p;
        prev->next = n;
        /* NOTE: do NOT move *head here. This branch is also reached when the
         * loop wrapped around (new exponent is the smallest), and in that case
         * the node must simply be appended after `prev` (the last node).
         * Moving head would break the descending order. */
    }
}

void create(struct Node **head)
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

void display(struct Node *head)
{
    if (head == NULL)
    {
        printf("0\n");
        return;
    }

    struct Node *p = head;
    int first = 1;

    do
    {
        if (p->coeff != 0)
        {
            if (!first && p->coeff > 0)
                printf(" + ");
            if (p->coeff < 0)
                printf(first ? "-" : " - ");

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
        }
        p = p->next;
    } while (p != head);

    if (first)
        printf("0");
    printf("\n");
}

struct Node *add(struct Node *a, struct Node *b)
{
    struct Node *result = NULL, *p = a, *q = b;
    int da = (a == NULL), db = (b == NULL);

    while (!da || !db)
    {
        if (da)
        {
            insert(&result, q->coeff, q->exp);
            q = q->next;
            if (q == b)
                db = 1;
        }
        else if (db)
        {
            insert(&result, p->coeff, p->exp);
            p = p->next;
            if (p == a)
                da = 1;
        }
        else if (p->exp == q->exp)
        {
            insert(&result, p->coeff + q->coeff, p->exp);
            p = p->next;
            q = q->next;
            if (p == a)
                da = 1;
            if (q == b)
                db = 1;
        }
        else if (p->exp > q->exp)
        {
            insert(&result, p->coeff, p->exp);
            p = p->next;
            if (p == a)
                da = 1;
        }
        else
        {
            insert(&result, q->coeff, q->exp);
            q = q->next;
            if (q == b)
                db = 1;
        }
    }
    return result;
}

void freeList(struct Node *head)
{
    if (head == NULL)
        return;
    struct Node *p = head->next;
    while (p != head)
    {
        struct Node *temp = p;
        p = p->next;
        free(temp);
    }
    free(head);
}

int main(void)
{
    struct Node *p1 = NULL, *p2 = NULL, *sum;

    printf("Polynomial 1\n");
    create(&p1);
    printf("Polynomial 2\n");
    create(&p2);

    printf("P1 = ");
    display(p1);
    printf("P2 = ");
    display(p2);

    sum = add(p1, p2);
    printf("Sum = ");
    display(sum);

    freeList(p1);
    freeList(p2);
    freeList(sum);
    return 0;
}
