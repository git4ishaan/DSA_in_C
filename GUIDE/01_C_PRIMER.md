# 01 — The Only C You Need

You do not need to learn all of C. You need about **15 concepts**. Every program in this
folder uses only these. Learn them once and every assignment becomes readable.

---

## 1. The anatomy of a C program

```c
#include <stdio.h>      /* printf, scanf            */
#include <stdlib.h>     /* malloc, free, exit       */
#include <string.h>     /* strcpy, strlen           */

#define MAX 100         /* a constant: MAX means 100 everywhere */

int globalVar = 0;      /* lives outside main, visible to all functions */

void myFunction(int x)  /* a function: input in brackets, no return value */
{
    printf("%d\n", x);
}

int main()              /* execution starts here, always */
{
    myFunction(5);
    return 0;           /* 0 = "program finished normally" */
}
```

Three things to remember:

- `#include` = "bring in a toolbox". `stdio.h` for input/output, `stdlib.h` for
  `malloc`/`free`, `string.h` for string functions.
- `main()` is where the program starts. Every C program has exactly one.
- Statements end with `;`. Braces `{ }` group statements. Indent for humans.

---

## 2. Variables and the types you will actually use

| Type | Means | Example | `printf` | `scanf` |
|------|-------|---------|----------|---------|
| `int` | whole number | `int n = 5;` | `%d` | `%d` |
| `float` | decimal, ~6 digits | `float m = 8.5;` | `%f` | `%f` |
| `char` | one character | `char c = 'A';` | `%c` | `%c` |
| `char s[50]` | string (array of chars) | `char s[] = "Ram";` | `%s` | `%s` |

**`scanf` needs `&` because it must write into your variable:**

```c
int n;
scanf("%d", &n);      /* CORRECT: & means "address of n" */

char name[50];
scanf("%s", name);    /* CORRECT: name is already an address */
```

`scanf("%d", n)` (missing `&`) is the #1 beginner crash. The program tries to write
to address `n`, which is some random garbage address.

**Reading a name with spaces:**

```c
scanf(" %49[^\n]", name);
```

- the space skips leftover newline from the previous `scanf`
- `49` is the maximum width (must be size of array − 1)
- `[^\n]` means "read until newline"

Plain `scanf("%s", name)` stops at the first space, so `"Ishaan Sharma"` becomes `"Ishaan"`.

---

## 3. Arrays — numbered boxes

```c
int a[5] = {10, 20, 30, 40, 50};
```

```
 index:   0     1     2     3     4
        +-----+-----+-----+-----+-----+
 value: | 10  | 20  | 30  | 40  | 50  |
        +-----+-----+-----+-----+-----+
```

**Indices go from 0 to n−1.** This is the source of countless bugs.

```c
for (int i = 0; i < 5; i++)     /* visits 0,1,2,3,4   */
    printf("%d ", a[i]);

printf("%d", a[5]);             /* WRONG: out of bounds, garbage or crash */
```

C does **not** check array bounds. Reading `a[5]` is undefined behaviour — it may print
garbage, may crash, may appear to work. That is why the exam tests loop bounds.

### 2D arrays

```c
int a[3][4];      /* 3 rows, 4 columns, 12 ints total */
```

```
        col 0   col 1   col 2   col 3
row 0  a[0][0] a[0][1] a[0][2] a[0][3]
row 1  a[1][0] a[1][1] a[1][2] a[1][3]
row 2  a[2][0] a[2][1] a[2][2] a[2][3]
```

Read with two loops, **row outer, column inner** (always keep this order):

```c
for (int i = 0; i < 3; i++)         /* i = row    */
    for (int j = 0; j < 4; j++)     /* j = column */
        scanf("%d", &a[i][j]);
```

In memory it is stored **row by row** (row-major order): all of row 0, then all of
row 1, etc. This is a very common viva question.

**Passing a 2D array to a function:** the function needs to know the row width.

```c
void display(int a[10][10], int m, int n)   /* 10 = declared max columns */
```

You must write the second dimension (`[10]`) or C cannot compute addresses.
The first dimension size is just documentation and is ignored.

---

## 4. Functions — the two ways to pass data

C passes arguments **by value**: the function gets a *copy*.

```c
void change(int x) { x = 99; }

int main() {
    int a = 5;
    change(a);
    printf("%d", a);     /* prints 5, NOT 99 */
}
```

So to let a function modify your variable, you pass its **address** (a pointer).

```c
void change(int *x) { *x = 99; }    /* *x = "the thing x points to" */

int main() {
    int a = 5;
    change(&a);          /* pass address */
    printf("%d", a);     /* prints 99 */
}
```

This is exactly why **push/pop use global variables** (`top`), and why linked-list
functions that change the head take `Node **head` ("pointer to pointer").

### The two symbols

| Symbol | Name | Meaning |
|--------|------|---------|
| `&x` | address-of | "where x lives" |
| `*p` | dereference | "the value stored at p" |

```c
int a = 5;
int *p = &a;        /* p holds the address of a */

printf("%d", a);    /* 5                     */
printf("%p", p);    /* 0x7ffe... (address)   */
printf("%d", *p);   /* 5  (go to address)    */

*p = 20;            /* changes a to 20       */
```

Picture it:

```
      p                        a
 +---------+             +---------+
 | 0x7ff.. | ----------> |   20    |
 +---------+             +---------+
   address of a           value of a
```

**Rules that prevent most bugs:**

- `p` is an address.
- `*p` is a value.
- `&a` is an address.
- Never use `*p` unless `p` points to something valid.

---

## 5. `struct` — making your own type

An array holds many values **of the same type**. A `struct` holds many values
**of different types** under one name.

```c
struct Student
{
    int roll;
    char name[50];
    float marks;
};
```

Use it:

```c
struct Student s1;          /* one student        */
struct Student s[100];      /* 100 students        */

s1.roll = 12;
strcpy(s1.name, "Ram");
s1.marks = 88.5;

printf("%d %s %.2f", s1.roll, s1.name, s1.marks);
```

For an **array** of structs use `.`; for a **pointer** to a struct use `->`:

```c
struct Student *p = &s1;
p->roll = 12;        /* same as (*p).roll = 12;  */
```

`->` is just a shorter `(*p).` . Use `->` whenever you have a pointer.

### `typedef` — stop typing `struct` every time

```c
typedef struct Student
{
    int roll;
    char name[50];
} Student;
```

Now `Student s1;` works. Your linked-list files do this:

```c
typedef struct node { ... } pnode;
```

### Self-referential struct (the linked list node)

```c
struct Node
{
    int data;
    struct Node *next;    /* pointer to the SAME type */
};
```

Why must it be `struct Node *next` and not `Node *next`? Because at that point
inside the struct, the name `Node` is not defined yet. The `struct Node` tag is.

**Viva answer:** *"A structure that contains a pointer to its own type is called a
self-referential structure. It is the basis of linked lists, trees and graphs."*

---

## 6. Dynamic memory — `malloc` and `free`

An array has fixed size. A linked list grows at runtime. That is what `malloc` is for.

```c
struct Node *p;

p = (struct Node *) malloc(sizeof(struct Node));

if (p == NULL)
{
    printf("Memory allocation failed\n");
    return;
}
```

Breaking it down:

| Part | Meaning |
|------|---------|
| `malloc(n)` | give me `n` bytes from the heap |
| `sizeof(struct Node)` | how many bytes one node needs |
| `(struct Node *)` | cast the returned `void *` to a node pointer |
| `p == NULL` | malloc failed (out of memory) |

Then use it, and **free** it:

```c
p->data = 10;
p->next = NULL;

free(p);        /* give the memory back */
p = NULL;       /* avoid a dangling pointer */
```

| Function | Meaning |
|----------|---------|
| `malloc(n)` | allocate `n` bytes, **uninitialised** |
| `calloc(k, n)` | allocate `k × n` bytes, **zero-filled** |
| `realloc(p, n)` | resize a block |
| `free(p)` | release a block |

**Viva answers:**

- *Memory leak* — allocating memory and losing the pointer without `free`.
- *Dangling pointer* — a pointer still holding the address of memory already freed.
- *`malloc` vs `calloc`* — `malloc` takes one size argument and does not initialise;
  `calloc` takes count and size and sets all bytes to 0.
- *Where does `malloc` get memory?* — the **heap**, not the stack.
- *`sizeof` is an operator, not a function.* It is evaluated at compile time.

---

## 7. Strings are just char arrays

```c
char s[50] = "hello";
```

```
 index:  0    1    2    3    4    5
       +----+----+----+----+----+----+
       | h  | e  | l  | l  | o  | \0 |
       +----+----+----+----+----+----+
```

Every string ends with `'\0'` (null character, value 0). That is how C knows where the
string stops. `strlen("hello")` is 5 because it does not count `'\0'`.

Common functions:

| Call | Does |
|------|------|
| `strlen(s)` | length (without `\0`) |
| `strcpy(d, s)` | copy s into d |
| `strcmp(a, b)` | 0 if equal, <0 if a<b, >0 if a>b |
| `strcat(a, b)` | append b to a |

Never compare strings with `==`. `if (s1 == s2)` compares addresses, not contents.
Use `strcmp(s1, s2) == 0`.

---

## 8. Loops and `switch` — the control flow you will use

```c
for (i = 0; i < n; i++) { }          /* known number of repetitions */
while (condition) { }                 /* repeat while true           */
do { } while (condition);             /* run at least once           */
```

`do-while` is used for **menus**: the menu must appear at least once, then repeat
until the user chooses Exit.

```c
switch (choice)
{
case 1:
    doSomething();
    break;              /* without break it "falls through" to case 2 */
case 2:
    doOther();
    break;
default:                /* anything else */
    printf("Invalid choice\n");
}
```

**Viva:** *"What happens if you forget `break` in a switch?"* → Execution falls through
into the next case and runs it too.

### Guard your menu against bad input

All the menu programs in this repo share a hidden infinite-loop bug. If the user types a
**letter** at the menu, `scanf("%d", &choice)` fails, `choice` keeps its old value, and the
loop repeats forever. If input **ends** (Ctrl+Z, or piped input), every `scanf` returns
`EOF` and the same thing happens.

That is fine for a normal interactive demo, but if the examiner pipes input or mistypes,
your program hangs. Two safe habits:

```c
int r = scanf("%d", &choice);

if (r == EOF)        /* input finished */
    break;

if (r != 1)          /* not a number: clear the bad characters */
{
    while (getchar() != '\n')
        ;
    continue;
}
```

This pattern is already used in `sll_workshop.c` (in the git history) and is worth
mentioning in viva: *"I check the return value of `scanf`, because it returns the number
of items successfully read."*

---

## 9. The five errors you will actually make

| Error | What you see | Fix |
|-------|--------------|-----|
| Missing `&` in `scanf` | crash / garbage | `scanf("%d", &n)` |
| Missing `;` | `error: expected ';'` | add it |
| Unmatched `{ }` | `error: expected '}' at end of input` | count braces |
| Used `->` on a non-pointer | `error: invalid type argument of '->'` | use `.` |
| Loop `i <= n` on an array | garbage last element / crash | `i < n` |

Compiler messages point to a **line number**. Fix the **first** error first; later
errors are often caused by the first one.

---

## 10. Hand-tracing — the skill that saves the exam

You cannot run code in a written exam, so you must **trace** it. Use a table:

```c
int a[5] = {5, 2, 9, 1, 7};
for (i = 0; i < 5; i++)
    if (a[i] > max) max = a[i];
```

| i | a[i] | a[i] > max ? | max |
|---|------|--------------|-----|
| initial | — | — | 0 (or a[0]) |
| 0 | 5 | yes | 5 |
| 1 | 2 | no | 5 |
| 2 | 9 | yes | 9 |
| 3 | 1 | no | 9 |
| 4 | 7 | no | 9 |

**Answer: 9.**

Do this for every loop in your answer. It proves the logic works and earns output marks.

---

## 11. A linked list in 10 lines (memorise this shape)

```c
struct Node { int data; struct Node *next; };

struct Node *head = NULL;                  /* empty list */

struct Node *n = malloc(sizeof(struct Node));   /* 1. create */
n->data = 10;                                   /* 2. fill   */
n->next = head;                                 /* 3. link   */
head = n;                                       /* 4. move head */
```

That is **insert at beginning**, O(1). Every other linked-list operation is a variation
of these four steps.

Traversal:

```c
struct Node *p = head;
while (p != NULL)
{
    printf("%d ", p->data);
    p = p->next;          /* move to next box */
}
```

The three things that break lists:

1. Losing `p->next` before you save it (`next = p->next;` first!).
2. Forgetting `p = p->next` → infinite loop.
3. Freeing a node then using it.

---

## 12. Quick self-test

Cover the answers.

1. What does `&` do in `scanf("%d", &n)`?
2. What is `*p` if `p = &a` and `a = 7`?
3. What is the last valid index of `int a[10]`?
4. Difference between `.` and `->`?
5. What does `malloc` return on failure?
6. Why does a string need `'\0'`?
7. What is a self-referential structure?
8. How many times does `for (i = 1; i <= n; i++)` run?
9. What does `free(p)` do, and what should you do after it?
10. Why does a function need `Node **head` to change the head?

<details>
<summary>Answers</summary>

1. Gives the address of `n`, so `scanf` can write into it.
2. `7`.
3. `9`.
4. `.` for a struct variable, `->` for a pointer to a struct.
5. `NULL`.
6. It marks the end; all string functions look for it.
7. A struct containing a pointer to its own type (linked-list node).
8. `n` times.
9. Releases heap memory; set the pointer to `NULL` to avoid a dangling pointer.
10. Because C passes by value — to change a caller's pointer you must pass its address.

</details>

---

**Next:** `02_MATRIX.md`
