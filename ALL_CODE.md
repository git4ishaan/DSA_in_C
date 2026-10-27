# All Assignment Code - DSA in C

Every C program in this folder, in one place.

- 12 programs covering 9 topics
- Code is copied exactly from the `.c` files, so every listing compiles as shown
- Each entry has a one-line purpose, a compile command, and the full code

> **Note:** `GUIDE/` also refers to programs that are no longer in the folder
> (saddle point, separate search/sort files, separate sparse files, `sll_workshop.c`).
> Only the files actually present are included here.

## Contents

| Topic | File(s) | Study chapter |
|-------|---------|---------------|
| Matrix operations | `Matrix_Operations.c` | `GUIDE/02_MATRIX.md` |
| Searching | `Searching_sorting.c` | `GUIDE/03_SEARCHING.md` |
| Sorting | `bubble_sort.c` | `GUIDE/04_SORTING.md` |
| Sparse matrix | `combi_sparse.c` | `GUIDE/05_SPARSE.md` |
| Stack | `stack.c`, `stack2.c` | `GUIDE/06_STACK.md` |
| Linear queue | `linear_queue.c` | `GUIDE/07_QUEUE.md` |
| Circular queue | `circular_queue.c` | `GUIDE/07_QUEUE.md` |
| Singly linked list | `singlyll.c` | `GUIDE/08_SLL.md` |
| Circular list and polynomials | `circlell.c`, `poly_add.c`, `poly_add_menu.c` | `GUIDE/09_CLL_POLY.md` |

## How to compile and run

```powershell
gcc <file>.c -o <file>.exe -Wall
.\<file>.exe
```

`poly_add.c` and `poly_add_menu.c` read their input without prompts unless
`poly_add_menu.c` is built with `-DINTERACTIVE`. The exact input format is described
in the comment at the top of `poly_add.c`; `circlell.c` is fully interactive.

---

## Matrix operations

Adds, subtracts, multiplies and transposes two matrices. The order is fixed at 3 x 3, and each run performs one operation chosen from the menu. Multiplication uses the three-loop row-by-column rule.

### `Matrix_Operations.c`

**What it does:** 3 x 3 matrix calculator: addition, subtraction, multiplication, transpose.

```powershell
gcc Matrix_Operations.c -o matrix_operations -Wall
.\matrix_operations.exe
```

```c
#include <stdio.h>
#include <stdlib.h>

void accept(int a[10][10], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Enter element[%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
}

void display(int a[10][10], int m, int n)
{
    printf("\nMatrix:\n");

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void add(int a[10][10], int b[10][10], int c[10][10], int m, int n)
{
    printf("\nEnter elements of Second Matrix:\n");
    accept(b, m, n);

    printf("\nAddition of Matrices:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] + b[i][j];
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

void subtract(int a[10][10], int b[10][10], int c[10][10], int m, int n)
{
    printf("\nEnter elements of Second Matrix:\n");
    accept(b, m, n);

    printf("\nSubtraction of Matrices:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] - b[i][j];
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

void mul(int a[10][10], int b[10][10], int c[10][10], int m, int n)
{
    printf("\nEnter elements of Second Matrix:\n");
    accept(b, m, n);

    printf("\nMultiplication of Matrices:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = 0;

            for (int k = 0; k < n; k++)
            {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }

            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

void trans(int a[10][10], int m, int n)
{
    int temp[10][10];

    printf("\nTranspose of Matrix:\n");

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[j][i] = a[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", temp[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int a[10][10], b[10][10], c[10][10];
    int m = 3, n = 3;
    int choice;

    printf("Enter elements of First Matrix:\n");
    accept(a, m, n);

    display(a, m, n);

    printf("\nChoose Function to Perform:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Transpose\n");
    printf("5. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        add(a, b, c, m, n);
        break;

    case 2:
        subtract(a, b, c, m, n);
        break;

    case 3:
        mul(a, b, c, m, n);
        break;

    case 4:
        trans(a, m, n);
        break;

    case 5:
        exit(0);

    default:
        printf("Invalid Choice!");
    }

    return 0;
}
```

---

## Searching

A student-record program with a menu. Linear search works on unsorted records; binary search needs the records sorted by roll number, so run a sort first. The same file also contains insertion, selection and shell sort.

### `Searching_sorting.c`

**What it does:** Student records with linear search, binary search, insertion sort, selection sort and shell sort.

```powershell
gcc Searching_sorting.c -o searching_sorting -Wall
.\searching_sorting.exe
```

```c
#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student
{
    int roll;
    char name[50];
    float marks;
};

/* Display students */
void display(struct Student s[], int n)
{
    printf("\n%-10s %-20s %-10s\n", "Roll No", "Name", "Marks");
    printf("---------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%-10d %-20s %-10.2f\n",
               s[i].roll, s[i].name, s[i].marks);
    }
}

/* Linear Search */
int linearSearch(struct Student s[], int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (s[i].roll == key)
            return i;
    }
    return -1;
}

/* Binary Search */
int binarySearch(struct Student s[], int n, int key)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (s[mid].roll == key)
            return mid;
        else if (s[mid].roll < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

/* Insertion Sort */
void insertionSort(struct Student s[], int n)
{
    for (int i = 1; i < n; i++)
    {
        struct Student temp = s[i];
        int j = i - 1;

        while (j >= 0 && s[j].roll > temp.roll)
        {
            s[j + 1] = s[j];
            j--;
        }

        s[j + 1] = temp;
    }
}

/* Selection Sort */
void selectionSort(struct Student s[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (s[j].roll < s[min].roll)
                min = j;
        }

        if (min != i)
        {
            struct Student temp = s[i];
            s[i] = s[min];
            s[min] = temp;
        }
    }
}

/* Shell Sort */
void shellSort(struct Student s[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {

        for (int i = gap; i < n; i++)
        {
            struct Student temp = s[i];
            int j = i;

            while (j >= gap &&
                   s[j - gap].roll > temp.roll)
            {
                s[j] = s[j - gap];
                j -= gap;
            }

            s[j] = temp;
        }
    }
}

int main()
{
    struct Student s[MAX];
    int n, choice, key, pos;

    printf("Enter number of students: ");
    scanf("%d", &n);

    printf("\nEnter student details:\n");

    for (int i = 0; i < n; i++)
    {
        printf("\nStudent %d\n", i + 1);

        printf("Roll No: ");
        scanf("%d", &s[i].roll);

        printf("Name: ");
        scanf("%s", s[i].name);

        printf("Marks: ");
        scanf("%f", &s[i].marks);
    }

    do
    {
        printf("\n===== MENU =====\n");
        printf("1. Display Records\n");
        printf("2. Linear Search\n");
        printf("3. Insertion Sort\n");
        printf("4. Selection Sort\n");
        printf("5. Shell Sort\n");
        printf("6. Binary Search\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            display(s, n);
            break;

        case 2:
            printf("Enter roll number to search: ");
            scanf("%d", &key);

            pos = linearSearch(s, n, key);

            if (pos != -1)
                printf("Student found at position %d.\n", pos + 1);
            else
                printf("Student not found.\n");

            break;

        case 3:
            insertionSort(s, n);
            printf("\nRecords sorted using Insertion Sort:\n");
            display(s, n);
            break;

        case 4:
            selectionSort(s, n);
            printf("\nRecords sorted using Selection Sort:\n");
            display(s, n);
            break;

        case 5:
            shellSort(s, n);
            printf("\nRecords sorted using Shell Sort:\n");
            display(s, n);
            break;

        case 6:
            printf("Enter roll number to search: ");
            scanf("%d", &key);

            pos = binarySearch(s, n, key);

            if (pos != -1)
                printf("Student found at position %d.\n", pos + 1);
            else
                printf("Student not found.\n");

            break;

        case 7:
            printf("Program terminated.\n");
            break;

        default:
            printf("Invalid choice.\n");
        }

    } while (choice != 7);

    return 0;
}
```

---

## Sorting

The smallest complete sorting program: read n integers and sort them with bubble sort. Use this one when the question asks only for bubble sort.

### `bubble_sort.c`

**What it does:** Bubble sort on an integer array.

```powershell
gcc bubble_sort.c -o bubble_sort -Wall
.\bubble_sort.exe
```

```c
#include <stdio.h>

int main()
{
    int arr[100], n, i, j, temp;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Bubble Sort
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("Sorted array:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
```

---

## Sparse matrix

Stores a sparse matrix in triplet form (row, column, value), then computes its transpose two ways: simple transpose and fast transpose using row counts and starting positions.

### `combi_sparse.c`

**What it does:** Matrix to sparse triplet, simple transpose, and fast transpose.

```powershell
gcc combi_sparse.c -o combi_sparse -Wall
.\combi_sparse.exe
```

```c
#include <stdio.h>

void accept(int a[10][10], int m, int n);
void displayMatrix(int a[10][10], int m, int n);
void sparse(int a[10][10], int b[20][3], int m, int n);
void displayTriplet(int b[20][3]);
void simpleTranspose(int a[20][3], int b[20][3]);
void fastTranspose(int a[20][3], int b[20][3]);

int main()
{
    int matrix[10][10];
    int sparseMatrix[20][3];
    int simple[20][3];
    int fast[20][3];
    int rows, cols;

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    accept(matrix, rows, cols);

    printf("\nOriginal Matrix:\n");
    displayMatrix(matrix, rows, cols);

    sparse(matrix, sparseMatrix, rows, cols);

    printf("\nSparse (Triplet) Matrix:\n");
    displayTriplet(sparseMatrix);

    simpleTranspose(sparseMatrix, simple);

    printf("\nSimple Transpose:\n");
    displayTriplet(simple);

    fastTranspose(sparseMatrix, fast);

    printf("\nFast Transpose:\n");
    displayTriplet(fast);

    return 0;
}

// Accept Matrix
void accept(int a[10][10], int m, int n)
{
    int i, j;

    printf("\nEnter Matrix Elements:\n");

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("Element[%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
}

// Display Original Matrix
void displayMatrix(int a[10][10], int m, int n)
{
    int i, j;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
}

// Convert Matrix to Sparse Triplet
void sparse(int a[10][10], int b[20][3], int m, int n)
{
    int i, j;
    int k = 1;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (a[i][j] != 0)
            {
                b[k][0] = i;
                b[k][1] = j;
                b[k][2] = a[i][j];
                k++;
            }
        }
    }

    b[0][0] = m;
    b[0][1] = n;
    b[0][2] = k - 1;
}

// Display Triplet Matrix
void displayTriplet(int b[20][3])
{
    int i;

    printf("Row\tCol\tValue\n");

    for (i = 0; i <= b[0][2]; i++)
    {
        printf("%d\t%d\t%d\n", b[i][0], b[i][1], b[i][2]);
    }
}

// Simple Transpose
void simpleTranspose(int a[20][3], int b[20][3])
{
    int i, j, k = 1;

    b[0][0] = a[0][1];
    b[0][1] = a[0][0];
    b[0][2] = a[0][2];

    for (i = 0; i < a[0][1]; i++)
    {
        for (j = 1; j <= a[0][2]; j++)
        {
            if (a[j][1] == i)
            {
                b[k][0] = a[j][1];
                b[k][1] = a[j][0];
                b[k][2] = a[j][2];
                k++;
            }
        }
    }
}

// Fast Transpose
void fastTranspose(int a[20][3], int b[20][3])
{
    int rowTerms[20], startPos[20];
    int i, j;

    b[0][0] = a[0][1];
    b[0][1] = a[0][0];
    b[0][2] = a[0][2];

    for (i = 0; i < a[0][1]; i++)
        rowTerms[i] = 0;

    for (i = 1; i <= a[0][2]; i++)
        rowTerms[a[i][1]]++;

    startPos[0] = 1;

    for (i = 1; i < a[0][1]; i++)
        startPos[i] = startPos[i - 1] + rowTerms[i - 1];

    for (i = 1; i <= a[0][2]; i++)
    {
        j = startPos[a[i][1]];

        b[j][0] = a[i][1];
        b[j][1] = a[i][0];
        b[j][2] = a[i][2];

        startPos[a[i][1]]++;
    }
}
```

---

## Stack

Two applications of a stack: converting an infix expression to postfix, and evaluating a postfix expression. Each is a separate program because both define main().

### `stack.c`

**What it does:** Infix to postfix conversion using a character stack. Handles + - * / ^ and parentheses.

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

### `stack2.c`

**What it does:** Postfix evaluation using an integer stack. Operands are single digits; spaces are ignored.

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
        /* Ignore spaces */
        if (expression[i] == ' ')
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

---

## Linear queue

Array-based queue for print jobs, with MAX = 5. Once rear reaches the end of the array the queue reports overflow, even if slots at the front were freed. That limitation is what the circular queue fixes.

### `linear_queue.c`

**What it does:** Linear queue: enqueue, dequeue and display pending print jobs.

```powershell
gcc linear_queue.c -o linear_queue -Wall
.\linear_queue.exe
```

```c
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
```

---

## Circular queue

Array-based circular queue for print jobs, also MAX = 5. Modulo arithmetic reuses freed slots, and the queue counts as full when (rear + 1) % MAX == front. Because empty is tracked with front = -1, all 5 slots are usable.

### `circular_queue.c`

**What it does:** Circular queue: enqueue, dequeue and display pending print jobs.

```powershell
gcc circular_queue.c -o circular_queue -Wall
.\circular_queue.exe
```

```c
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
```

---

## Singly linked list

A workshop enrollment list. New students are appended at the end; removal works for the head as well as any later node. Sorting swaps the data inside nodes, while reversal relinks the nodes.

### `singlyll.c`

**What it does:** Workshop enrollment: add, remove, display, count, sort and reverse students.

```powershell
gcc singlyll.c -o singlyll -Wall
.\singlyll.exe
```

```c
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
```

---

## Circular linked list and polynomials

Three versions of polynomial addition with a circular singly linked list. Terms are kept in descending exponent order, duplicate exponents are combined, and terms whose coefficient becomes zero are removed.

### `circlell.c`

**What it does:** Interactive polynomial addition with prompts. Builds two polynomials, then prints P1, P2 and Sum.

```powershell
gcc circlell.c -o circlell -Wall
.\circlell.exe
```

```c
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
```

### `poly_add.c`

**What it does:** Same polynomial addition in auto-grader format: no prompts. Input is n, then n coefficient/exponent pairs, for each polynomial. Output is exactly P1, P2, SUM.

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

### `poly_add_menu.c`

**What it does:** One-term-at-a-time version. Prompts appear only when compiled with -DINTERACTIVE; without it the input is read silently.

```powershell
gcc -DINTERACTIVE poly_add_menu.c -o poly_add_menu -Wall
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

