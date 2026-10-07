/*
 * Assignment: Polynomial Addition using a Circular Singly Linked List
 *
 * Complete every function marked TODO. Do NOT change main(), print_poly()
 * or the input/output format - your program is graded automatically.
 *
 * INPUT (no prompts are printed):
 *   n1                number of terms in polynomial 1
 *   coef exp          n1 lines, terms in ANY order, exponents >= 0
 *   n2                number of terms in polynomial 2
 *   coef exp          n2 lines
 *
 * OUTPUT (exactly three lines):
 *   P1 = <poly>
 *   P2 = <poly>
 *   SUM = <poly>
 *
 * <poly> lists terms in DESCENDING order of exponent as "%+dx^%d" separated
 * by one space, e.g. "+3x^2 -5x^0". A polynomial with no terms prints "0".
 *
 * Rules:
 *   - Terms with the same exponent (even inside one polynomial) are combined.
 *   - Terms whose coefficient becomes 0 must be removed.
 *   - The list is circular with a header node; head->next == head when empty.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int coef;
    int exp;
    struct node *next;
} pnode;

/* Create an empty circular list (header node only) and return the header. */
pnode *new_poly(void)
{
    pnode *head = (pnode *)malloc(sizeof(pnode));
    if (head != NULL) {
        head->coef = 0;
        head->exp = -1;  /* Dummy value for header */
        head->next = head; /* Circular link back to itself */
    }
    return head;
}

/* Insert a term keeping the list in descending exponent order.
 * Combine with an existing term of the same exponent; remove it if the
 * resulting coefficient is 0. Ignore terms whose coefficient is 0. */
void insert_term(pnode *head, int coef, int exp)
{
    if (coef == 0) {
        return;
    }

    pnode *prev = head;
    pnode *curr = head->next;

    /* Traverse to find the correct insertion position (descending order) */
    while (curr != head && curr->exp > exp) {
        prev = curr;
        curr = curr->next;
    }

    /* If a term with the exact exponent already exists, combine them */
    if (curr != head && curr->exp == exp) {
        curr->coef += coef;
        
        /* If combining results in a coefficient of 0, remove the node */
        if (curr->coef == 0) {
            prev->next = curr->next;
            free(curr);
        }
    } 
    /* Otherwise, insert a new term in its sorted position */
    else {
        pnode *new_node = (pnode *)malloc(sizeof(pnode));
        if (new_node != NULL) {
            new_node->coef = coef;
            new_node->exp = exp;
            
            new_node->next = curr;
            prev->next = new_node;
        }
    }
}

/* Read one polynomial from stdin in the format described above. */
pnode *read_poly(void)
{
    pnode *head = new_poly();
    int n, coef, exp;

    if (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            if (scanf("%d %d", &coef, &exp) == 2) {
                insert_term(head, coef, exp);
            }
        }
    }
    return head;
}

/* Return a NEW polynomial equal to h1 + h2. Do not modify h1 or h2. */
pnode *poly_add(pnode *h1, pnode *h2)
{
    pnode *sum = new_poly();
    pnode *curr;

    /* Insert all terms from the first polynomial */
    curr = h1->next;
    while (curr != h1) {
        insert_term(sum, curr->coef, curr->exp);
        curr = curr->next;
    }

    /* Insert all terms from the second polynomial */
    curr = h2->next;
    while (curr != h2) {
        insert_term(sum, curr->coef, curr->exp);
        curr = curr->next;
    }

    return sum;
}

/* Release every node including the header. */
void free_poly(pnode *head)
{
    if (head == NULL) {
        return;
    }
    
    pnode *curr = head->next;
    
    while (curr != head) {
        pnode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    
    /* Finally, free the header node itself */
    free(head);
}

/* ---------------- provided - do not modify ---------------- */
void print_poly(pnode *head)
{
    pnode *p = head->next;

    if (p == head) {
        printf("0\n");
        return;
    }
    while (p != head) {
        printf("%+dx^%d", p->coef, p->exp);
        p = p->next;
        if (p != head)
            printf(" ");
    }
    printf("\n");
}

int main(void)
{
    pnode *p1 = read_poly();
    pnode *p2 = read_poly();
    pnode *sum = poly_add(p1, p2);

    printf("P1 = ");  print_poly(p1);
    printf("P2 = ");  print_poly(p2);
    printf("SUM = "); print_poly(sum);

    free_poly(p1);
    free_poly(p2);
    free_poly(sum);
    return 0;
}