# Assignment Code — 1, 2, 3, 8, 9

C programs for five of the nine lab assignments, in one file for quick reference.

- Code is copied exactly from the `.c` files, so every listing compiles as shown
- Each assignment has its problem statement, compile command and full code
- The `_simple` queue files are smaller integer-only variants of the print-job programs

## Contents

| # | Assignment | File(s) |
|---|------------|---------|
| 1 | Matrix operations | `Matrix_Operations.c` |
| 2 | Sparse matrix (simple & fast transpose) | `combi_sparse.c` |
| 3 | Searching and sorting | `Searching_sorting.c`, `bubble_sort.c` |
| 8 | Linear queue (printer jobs) | `linear_queue.c`, `linear_queue_simple.c` |
| 9 | Circular queue (printer jobs) | `circular_queue.c`, `circular_queue_simple.c` |

## How to compile and run

```powershell
gcc <file>.c -o <file>.exe -Wall
.\<file>.exe
```

All five programs are interactive: they read input from the keyboard, so run them
from a terminal and type the values when prompted.

---

# Assignment 1 — Matrix Operations

**Problem statement:** Write a C program to perform basic matrix operations such as
addition, subtraction, multiplication and transpose of a matrix using two-dimensional
arrays.

**What it does:** 3 x 3 matrix calculator. Reads the first matrix, then asks for one
operation and (except for transpose) reads the second matrix.

**Formulas used:**

| Operation | Condition | Formula |
|-----------|-----------|---------|
| Addition | Same order | `C[i][j] = A[i][j] + B[i][j]` |
| Subtraction | Same order | `C[i][j] = A[i][j] - B[i][j]` |
| Multiplication | Columns of A = rows of B | `C[i][j] = sum(A[i][k] * B[k][j])` |
| Transpose | Always possible | `AT[i][j] = A[j][i]` |

**Complexity:** addition/subtraction/transpose `O(m*n)`; multiplication `O(m*n*p)`,
here `O(n^3)` for a square matrix. Space `O(m*n)`.

### `Matrix_Operations.c`

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

# Assignment 2 — Sparse Matrix

**Problem statement:** Write a C program for sparse matrix realization and operations
on it: transpose and fast transpose.

**What it does:** Reads a dense matrix, counts zeros and non-zeros, converts it to
3-tuple (triplet) form, then prints both the simple transpose and the fast transpose.

**Triplet form:** row `0` of the compact table stores `rows`, `columns` and `non-zero
count`; every later row stores `row`, `column`, `value` of one non-zero element.

**Complexity:** simple transpose `O(columns * non-zeros)`; fast transpose
`O(columns + non-zeros)`. Space `O(non-zeros)` for each table.

### `combi_sparse.c`

Input format: number of rows, number of columns, then every element of the matrix.

```powershell
gcc combi_sparse.c -o combi_sparse -Wall
.\combi_sparse.exe
```

```c
#include <stdio.h>
void accept(int a[10][10], int rows, int coln);
void declare(int a[10][10], int rows, int coln);
void compact(int a[10][10], int rows, int coln, int s[20][3]);
void simpletranspose(int nz, int s[20][3]);
void fasttranspose(int nz, int s[20][3]);

void accept(int a[10][10], int rows, int coln)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < coln; j++)
        {
            printf("Enter a no:");
            scanf("%d", &a[i][j]);
        }
    }
}
void declare(int a[10][10], int rows, int coln)
{
    int i, j;
    printf("The matrix is:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < coln; j++)
        {
            printf("\t%d", a[i][j]);
        }
        printf("\n");
    }
}
void compact(int a[10][10], int rows, int coln, int s[20][3])
{
    int i, j, z = 0, nz = 0;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < coln; j++)
        {
            if (a[i][j] == 0)
                z++;
            else
                nz++;
        }
    }
    if (nz > z)
    {
        printf("It is not a sparse matrix\n");
    }
    else
    {
        s[0][0] = rows;
        s[0][1] = coln;
        s[0][2] = nz;
        int k = 1;
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < coln; j++)
            {
                if (a[i][j] != 0)
                {
                    s[k][0] = i;
                    s[k][1] = j;
                    s[k][2] = a[i][j];
                    k++;
                }
            }
        }
        printf("\nThe sparse matrix is:\n");
        printf("row\tcol\tvalue\n");
        for (i = 0; i < nz + 1; i++)
        {
            for (j = 0; j < 3; j++)
            {
                printf("%d\t", s[i][j]);
            }
            printf("\n");
        }
    }
}
void simpletranspose(int nz, int s[20][3])
{
    int t[20][3];
    int i, j, k = 1;
    t[0][0] = s[0][1];
    t[0][1] = s[0][0];
    t[0][2] = s[0][2];

    for (i = 0; i < s[0][1]; i++)
    {
        for (j = 1; j <= nz; j++)
        {
            if (s[j][1] == i)
            {
                t[k][0] = s[j][1];
                t[k][1] = s[j][0];
                t[k][2] = s[j][2];
                k++;
            }
        }
    }
    printf("\nThe Simple transpose is :\n");
    printf("row\tcol\tvalue\n");
    for (i = 0; i < nz + 1; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%d\t", t[i][j]);
        }
        printf("\n");
    }
}
void fasttranspose(int nz, int s[20][3])
{
    int t[20][3];
    int S[20] = {0}, T[20] = {0};
    int i, j;
    t[0][0] = s[0][1];
    t[0][1] = s[0][0];
    t[0][2] = s[0][2];
    if (nz == 0)
    {
        printf("\nFast transpose is:\n");
        printf("%d\t%d\t%d\n", t[0][0], t[0][1], t[0][2]);
        return;
    }
    for (i = 0; i < s[0][1]; i++)
        S[i] = 0;
    for (i = 1; i <= nz; i++)
        S[s[i][1]]++;
    T[0] = 1;
    for (i = 1; i < s[0][1]; i++)
        T[i] = T[i - 1] + S[i - 1];
    for (i = 1; i <= nz; i++)
    {
        j = T[s[i][1]];
        t[j][0] = s[i][1];
        t[j][1] = s[i][0];
        t[j][2] = s[i][2];
        T[s[i][1]]++;
    }
    printf("\nThe Fast Transpose is:\n");
    printf("Row\tCol\tValue\n");

    for (i = 0; i <= nz; i++)
    {
        printf("%d\t%d\t%d\n", t[i][0], t[i][1], t[i][2]);
    }
}
int main()
{
    int a[10][10], rows, coln, i, j;
    int s[20][3];
    int nz;
    printf("Enter no of rows and columns:");
    scanf("%d%d", &rows, &coln);
    accept(a, rows, coln);
    declare(a, rows, coln);
    compact(a, rows, coln, s);
    nz = s[0][2];
    simpletranspose(nz, s);
    fasttranspose(nz, s);
    return 0;
}
```

---

# Assignment 3 — Searching and Sorting

**Problem statement:** Create a student database using an array of structures. Apply
searching (linear and binary search) and sorting techniques (insertion sort, selection
sort and shell sort).

**What it does:** Stores `roll`, `name` and `marks` for up to 100 students and gives a
menu to display, search, sort and exit. Binary search always sorts by roll number
first, because binary search only works on sorted data.

**Algorithms included:**

| Technique | Best | Average | Worst | Notes |
|-----------|------|---------|-------|-------|
| Linear search | `O(1)` | `O(n)` | `O(n)` | Works on unsorted data |
| Binary search | `O(1)` | `O(log n)` | `O(log n)` | Needs sorted data |
| Insertion sort | `O(n)` | `O(n^2)` | `O(n^2)` | Stable, in-place |
| Selection sort | `O(n^2)` | `O(n^2)` | `O(n^2)` | Not stable, in-place |
| Shell sort | `O(n log n)` | Depends on gap | `O(n^2)` | In-place |
| Bubble sort | `O(n)` | `O(n^2)` | `O(n^2)` | Stable, in-place |

### `Searching_sorting.c`

Input format: number of students, then for each student `roll name marks`.

```powershell
gcc Searching_sorting.c -o searching_sorting -Wall
.\searching_sorting.exe
```

```c
#include <stdio.h>
#define MAX 100

struct Student
{
    int roll;
    char name[50];
    float marks;
};

void display(struct Student s[], int n)
{
    int i;

    printf("\nRoll\tName\tMarks\n");

    for (i = 0; i < n; i++)
        printf("%d\t%s\t%.2f\n", s[i].roll, s[i].name, s[i].marks);
}

int linearSearch(struct Student s[], int n, int key)
{
    int i;

    for (i = 0; i < n; i++)
        if (s[i].roll == key)
            return i;

    return -1;
}

int binarySearch(struct Student s[], int n, int key)
{
    int low = 0, high = n - 1, mid;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (s[mid].roll == key)
            return mid;
        else if (s[mid].roll < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

void insertionSort(struct Student s[], int n)
{
    int i, j;
    struct Student temp;

    for (i = 1; i < n; i++)
    {
        temp = s[i];
        j = i - 1;

        while (j >= 0 && s[j].roll > temp.roll)
        {
            s[j + 1] = s[j];
            j--;
        }

        s[j + 1] = temp;
    }
}

void selectionSort(struct Student s[], int n)
{
    int i, j, min;
    struct Student temp;

    for (i = 0; i < n - 1; i++)
    {
        min = i;

        for (j = i + 1; j < n; j++)
            if (s[j].roll < s[min].roll)
                min = j;

        temp = s[i];
        s[i] = s[min];
        s[min] = temp;
    }
}

void shellSort(struct Student s[], int n)
{
    int gap, i, j;
    struct Student temp;

    for (gap = n / 2; gap > 0; gap = gap / 2)
    {
        for (i = gap; i < n; i++)
        {
            temp = s[i];
            j = i;

            while (j >= gap && s[j - gap].roll > temp.roll)
            {
                s[j] = s[j - gap];
                j = j - gap;
            }

            s[j] = temp;
        }
    }
}

int main()
{
    struct Student s[MAX];
    int n, i, choice, key, pos;

    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of students.\n");
        return 0;
    }

    for (i = 0; i < n; i++)
    {
        printf("\nEnter roll number, name and marks:\n");
        scanf("%d %49s %f", &s[i].roll, s[i].name, &s[i].marks);
    }

    do
    {
        printf("\n1. Display");
        printf("\n2. Linear Search");
        printf("\n3. Insertion Sort");
        printf("\n4. Selection Sort");
        printf("\n5. Shell Sort");
        printf("\n6. Binary Search");
        printf("\n7. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                display(s, n);
                break;

            case 2:
                printf("Enter roll number: ");
                scanf("%d", &key);

                pos = linearSearch(s, n, key);

                if (pos == -1)
                    printf("Student not found.\n");
                else
                    printf("Student found at position %d.\n", pos + 1);
                break;

            case 3:
                insertionSort(s, n);
                display(s, n);
                break;

            case 4:
                selectionSort(s, n);
                display(s, n);
                break;

            case 5:
                shellSort(s, n);
                display(s, n);
                break;

            case 6:
                insertionSort(s, n);
                printf("Enter roll number: ");
                scanf("%d", &key);

                pos = binarySearch(s, n, key);

                if (pos == -1)
                    printf("Student not found.\n");
                else
                    printf("Student found at position %d.\n", pos + 1);
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

### `bubble_sort.c` (extra sorting program)

Bubble sort on a plain integer array. Not part of the student-database menu, but it is
the standard bubble sort used in the same assignment.

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

# Assignment 8 — Linear Queue

**Problem statement:** In a networked environment, a shared printer receives multiple
print requests. Implement a linear queue to manage the print jobs, each identified by a
Job ID and a Document Title, and process them in FIFO order.

**What it does:** Menu-driven linear queue of print jobs with enqueue, dequeue and
display. Overflow is checked with `rear == MAX - 1`, underflow with `front == -1 ||
front > rear`.

**Complexity:** enqueue, dequeue and display are all `O(1)` except display, which is
`O(k)` for `k` pending jobs. Space `O(MAX)`.

**Limitation:** after deletions, the space at the front cannot be reused because `rear`
never moves backwards. That is exactly the problem the circular queue (assignment 9)
solves.

### `linear_queue.c`

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

### `linear_queue_simple.c` (integer-only variant)

Same linear queue logic on plain integers, with shorter prompts.

```powershell
gcc linear_queue_simple.c -o linear_queue_simple -Wall
.\linear_queue_simple.exe
```

```c
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
```

---

# Assignment 9 — Circular Queue

**Problem statement:** Simulate a printer queue manager using a circular queue
implemented with an array: add a print job, process a print job, and display all
pending print jobs.

**What it does:** Same menu as the linear queue, but `rear` and `front` wrap around
with `% MAX`, so positions freed by dequeue are reused.

**Key conditions:**

| Case | Condition |
|------|-----------|
| Queue full (overflow) | `(rear + 1) % MAX == front` |
| Queue empty (underflow) | `front == -1` |
| Advance rear | `rear = (rear + 1) % MAX` |
| Advance front | `front = (front + 1) % MAX` |

One slot is deliberately left unused so full and empty can be told apart. Usable
capacity is therefore `MAX - 1` jobs.

**Complexity:** enqueue and dequeue `O(1)`; display `O(k)`; space `O(MAX)`.

### `circular_queue.c`

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

### `circular_queue_simple.c` (integer-only variant)

Same circular queue logic on plain integers, with shorter prompts.

```powershell
gcc circular_queue_simple.c -o circular_queue_simple -Wall
.\circular_queue_simple.exe
```

```c
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
```
