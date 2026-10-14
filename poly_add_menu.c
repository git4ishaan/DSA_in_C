
/*
 * Assignment: Polynomial Addition using a Circular Singly Linked List
 *             (terms entered one at a time)
 */
#include <stdio.h>
#include <stdlib.h>

#ifdef INTERACTIVE
#define PROMPT(...) printf(__VA_ARGS__)
#else
#define PROMPT(...)
#endif

typedef struct node
{
    int coef;
    int exp;
    struct node *next;
} pnode;

/* Create an empty circular list (header node only) and return the header. */
pnode *new_poly(void)
{
    pnode *head = (pnode *)malloc(sizeof(pnode));

    if (head == NULL)
        return NULL;

    head->coef = 0;
    head->exp = 0;
    head->next = head;

    return head;
}

/* Insert a term in descending exponent order. */
void insert_term(pnode *head, int coef, int exp)
{
    pnode *prev, *curr, *temp;

    if (head == NULL || coef == 0)
        return;

    prev = head;
    curr = head->next;

    /* Find the correct position. */
    while (curr != head && curr->exp > exp)
    {
        prev = curr;
        curr = curr->next;
    }

    /* Combine terms with the same exponent. */
    if (curr != head && curr->exp == exp)
    {
        curr->coef += coef;

        /* Remove the term if its coefficient becomes zero. */
        if (curr->coef == 0)
        {
            prev->next = curr->next;
            free(curr);
        }
        return;
    }

    /* Create and insert a new term. */
    temp = (pnode *)malloc(sizeof(pnode));

    if (temp == NULL)
        return;

    temp->coef = coef;
    temp->exp = exp;
    temp->next = curr;
    prev->next = temp;
}

/* Read one polynomial. */
pnode *read_poly(void)
{
    pnode *head = NULL;
    int ch, c, e;

    /* Create the empty polynomial. */
    head = new_poly();

    if (head == NULL)
        return NULL;

    while (1)
    {
        PROMPT("Do you want to enter a term? (1 = yes, 0 = no): "); // provided
        if (scanf("%d", &ch) != 1 || ch != 1)                       // provided
            break;                                                  // provided
        PROMPT("Enter coefficient and exponent: ");                 // provided
        if (scanf("%d %d", &c, &e) != 2)                            // provided
            break;                                                  // provided

        /* Add the term c*x^e to the polynomial. */
        insert_term(head, c, e);
    }

    return head;
}

/* Return a NEW polynomial equal to h1 + h2. */
pnode *poly_add(pnode *h1, pnode *h2)
{
    pnode *sum = new_poly();
    pnode *p;

    if (sum == NULL)
        return NULL;

    /* Copy all terms from the first polynomial. */
    if (h1 != NULL)
    {
        for (p = h1->next; p != h1; p = p->next)
        {
            insert_term(sum, p->coef, p->exp);
        }
    }

    /* Add all terms from the second polynomial. */
    if (h2 != NULL)
    {
        for (p = h2->next; p != h2; p = p->next)
        {
            insert_term(sum, p->coef, p->exp);
        }
    }

    return sum;
}

/* Release every node including the header. */
void free_poly(pnode *head)
{
    pnode *curr, *temp;

    if (head == NULL)
        return;

    curr = head->next;

    while (curr != head)
    {
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    free(head);
}

/* ---------------- provided - do not modify ---------------- */
void print_poly(pnode *head)
{
    pnode *p = head->next;

    if (p == head)
    {
        printf("0\n");
        return;
    }
    while (p != head)
    {
        printf("%+dx^%d", p->coef, p->exp);
        p = p->next;
        if (p != head)
            printf(" ");
    }
    printf("\n");
}

int main(void)
{
    PROMPT("Enter the first polynomial\n");
    pnode *p1 = read_poly();
    PROMPT("Enter the second polynomial\n");
    pnode *p2 = read_poly();
    pnode *sum = poly_add(p1, p2);

    printf("P1 = ");
    print_poly(p1);
    printf("P2 = ");
    print_poly(p2);
    printf("SUM = ");
    print_poly(sum);

    free_poly(p1);
    free_poly(p2);
    free_poly(sum);
    return 0;
}
