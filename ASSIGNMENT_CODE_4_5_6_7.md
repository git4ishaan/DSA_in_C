# Assignment Code — 4, 5, 6, 7

C programs for the remaining four lab assignments: linked lists, polynomials and stacks.

- Code is copied exactly from the `.c` files, so every listing compiles as shown
- Each assignment has its problem statement, compile command and full code
- Companion file: [`ASSIGNMENT_CODE_1_2_3_8_9.md`](ASSIGNMENT_CODE_1_2_3_8_9.md)

## Contents

| # | Assignment | File(s) |
|---|------------|---------|
| 4 | Singly linked list (workshop enrollment) | `singlyll.c` |
| 5 | Circular linked list + polynomial addition | `circlell.c`, `poly_add.c`, `poly_add_menu.c` |
| 6 | Stack: infix to postfix conversion | `stack.c` |
| 7 | Stack: postfix expression evaluation | `stack2.c` |

## How to compile and run

```powershell
gcc <file>.c -o <file>.exe -Wall
.\<file>.exe
```

`poly_add_menu.c` reads its input silently unless it is compiled with `-DINTERACTIVE`:

```powershell
gcc -DINTERACTIVE poly_add_menu.c -o poly_add_menu -Wall
```

---

# Assignment 4 — Singly Linked List

**Problem statement:** The Department of Computer Engineering is organizing a technical
workshop for which students can register in advance. The registration data is maintained
using a singly linked list, where each student has a Registration Number and a Name.
Implement: (a) add a student, (b) remove a student, (c) display the list, (d) count total
participants, (e) sort the list, (f) reverse the list.

**What it does:** Menu-driven workshop enrollment system. New students are appended at
the tail, removal searches by registration number and unlinks the node, sort is a bubble
sort that swaps only data (not pointers), and reverse rewires the `next` pointers in place.

**Complexity:**

| Operation | Time | Why |
|-----------|------|-----|
| Add student | `O(n)` | Walks to the tail to append |
| Remove student | `O(n)` | Linear search by RegNo |
| Display | `O(n)` | One pass |
| Count | `O(n)` | One pass |
| Sort | `O(n^2)` | Bubble sort on the nodes |
| Reverse | `O(n)` | One pass, three pointers |
| Space | `O(n)` | One node per student |

### `singlyll.c`

```powershell
gcc singlyll.c -o singlyll -Wall
.\singlyll.exe
```

```c
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
```

---

# Assignment 5 — Circular Linked List and Polynomial Addition

**Problem statement:** Implement polynomial operations using a circular linked list:
create a polynomial by inserting terms, display it in readable mathematical form, and add
two polynomials and display the result.

**Node layout:** each node stores `coeff`, `exp` and `next`. A header (dummy) node is
always present, and `head->next == head` means the polynomial is empty. Terms are kept in
descending exponent order; inserting an exponent that already exists combines the
coefficients, and a term that becomes zero is deleted.

**Complexity:**

| Operation | Time | Why |
|-----------|------|-----|
| Insert one term | `O(n)` | Find the position in descending order |
| Create n terms | `O(n^2)` | n insertions |
| Display | `O(n)` | One circular traversal |
| Add two polynomials | `O((n+m)^2)` | Every term re-inserted into the sum |
| Space | `O(n)` | One node per term |

## Program 1: `circlell.c` (interactive, pretty output)

Fully interactive. Builds two polynomials and prints `P1 = ...`, `P2 = ...`,
`Sum = ...` using proper `+` / `-` signs, omitting coefficient `1` and handling
exponent `0` and `1`.

```powershell
gcc circlell.c -o circlell -Wall
.\circlell.exe
```

```c
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
```

## Program 2: `poly_add.c` (auto-grader format, no prompts)

Prints only three lines: `P1 = ...`, `P2 = ...`, `SUM = ...`, each term formatted as
`%+dx^%d`. This is the version to submit when the checker expects exact output.

**Input format (no prompts):**

```text
n1
coef exp        (n1 lines)
n2
coef exp        (n2 lines)
```

Example input:

```text
3
3 2
2 1
1 0
2
-1 1
5 0
```

Example output:

```text
P1 = +3x^2 +2x^1 +1x^0
P2 = -1x^1 +5x^0
SUM = +3x^2 +1x^1 +6x^0
```

```powershell
gcc poly_add.c -o poly_add -Wall
.\poly_add.exe < input.txt
```

```c
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
```

## Program 3: `poly_add_menu.c` (one term at a time)

Same polynomial addition, but the user enters terms one at a time. For each polynomial
type `1` followed by `coef exp`, and type `0` to finish that polynomial.

```text
1
3 2
1
2 1
0
1
-1 1
0
```

Prompts appear only when compiled with `-DINTERACTIVE`; without it the input is read
silently so the same file also works with an auto-grader.

```powershell
gcc poly_add_menu.c -o poly_add_menu -Wall
.\poly_add_menu.exe
```

```c

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
```

---

# Assignment 6 — Infix to Postfix Conversion

**Problem statement:** Implement stack as an ADT and apply it for expression conversion.
This program performs the infix to postfix conversion.

**What it does:** Uses a character stack of size 100. Operands go straight to the output,
`(` is pushed, `)` pops until the matching `(`, and an operator pops every stacked operator
with greater or equal precedence before it is pushed.

**Operator precedence:** `^` = 3, `*` `/` = 2, `+` `-` = 1.

**Complexity:** `O(n)` time (each character pushed and popped at most once) and `O(n)`
space for the stack and the result.

**Limits to know for viva:** operands are treated as single characters (`isalnum`), so
multi-digit numbers and multi-letter names are not supported. Because the comparison uses
`>=`, `^` is handled left-associatively.

### `stack.c`

```powershell
gcc stack.c -o stack -Wall
.\stack.exe
```

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

/* Push */
void push(char ch)
{
    if (top == MAX - 1)
        printf("Stack Overflow\n");
    else
        stack[++top] = ch;
}

/* Pop */
char pop()
{
    if (top == -1)
        return '\0';

    return stack[top--];
}

/* Peek */
char peek()
{
    if (top == -1)
        return '\0';

    return stack[top];
}

/* Precedence */
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    if (op == '^')
        return 3;

    return 0;
}

/* Infix to Postfix */
void infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char ch;

    top = -1;

    for (i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        /* Operand */
        if (isalnum(ch))
        {
            postfix[j++] = ch;
        }

        /* Opening bracket */
        else if (ch == '(')
        {
            push(ch);
        }

        /* Closing bracket */
        else if (ch == ')')
        {
            while (top != -1 && peek() != '(')
                postfix[j++] = pop();

            pop(); // Remove '('
        }

        /* Operator */
        else
        {
            while (top != -1 &&
                   precedence(peek()) >= precedence(ch))
            {
                postfix[j++] = pop();
            }

            push(ch);
        }
    }

    /* Pop remaining operators */
    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';
}

/* Main */
int main()
{
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
```

**Dry run:** `A+B*C` -> operands `A`; `+` pushed; `B`; `*` has higher precedence so it is
pushed; `C`; end of input pops `*` then `+` -> `ABC*+`.

---

# Assignment 7 — Postfix Expression Evaluation

**Problem statement:** Write a C program to evaluate a postfix expression using a stack.

**What it does:** Reads a whole line with `fgets`. Digits are pushed as integers,
whitespace is skipped, and each operator pops two operands, applies the operation and
pushes the result. The final stack value is the answer.

**Note the pop order:** `operand2` is popped first and `operand1` second, so `8 3 -`
correctly gives `5` (`operand1 - operand2`), not `-5`.

**Complexity:** `O(n)` time and `O(n)` space.

**Limits to know for viva:** operands are single digits only (no multi-digit numbers,
since each digit is pushed separately) and `/` is integer division.

### `stack2.c`

```powershell
gcc stack2.c -o stack2 -Wall
.\stack2.exe
```

```c
#include <stdio.h>
#include <ctype.h>

#define MAX 100

int stack[MAX];
int top = -1;

/* Push */
void push(int value)
{
    if (top == MAX - 1)
        printf("Stack Overflow\n");
    else
        stack[++top] = value;
}

/* Pop */
int pop()
{
    if (top == -1)
    {
        printf("Stack Underflow\n");
        return -1;
    }

    return stack[top--];
}

/* Evaluate Postfix Expression */
int evaluatePostfix(char expression[])
{
    int i;
    int operand1, operand2, result;

    for (i = 0; expression[i] != '\0'; i++)
    {
        /* Ignore whitespace, including the newline left by fgets */
        if (isspace((unsigned char)expression[i]))
            continue;

        /* If operand, push it */
        if (isdigit(expression[i]))
        {
            push(expression[i] - '0');
        }

        /* If operator */
        else
        {
            operand2 = pop();
            operand1 = pop();

            switch (expression[i])
            {
            case '+':
                result = operand1 + operand2;
                break;

            case '-':
                result = operand1 - operand2;
                break;

            case '*':
                result = operand1 * operand2;
                break;

            case '/':
                result = operand1 / operand2;
                break;

            default:
                printf("Invalid operator\n");
                return -1;
            }

            push(result);
        }
    }

    return pop();
}

int main()
{
    char expression[MAX];
    int result;

    printf("Enter postfix expression: ");
    fgets(expression, MAX, stdin);

    result = evaluatePostfix(expression);

    printf("Result = %d\n", result);

    return 0;
}
```

**Dry run:** `35+4*` -> push 3, push 5, `+` gives 8, push 4, `*` gives 32 -> `Result = 32`.
