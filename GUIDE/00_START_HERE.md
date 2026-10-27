# DSA in C — External Exam Mentor Guide

You have 21 `.c` files in this folder. They are really **10 assignments**, and every one of
them follows the same exam pattern:

```
CONCEPT  ->  ALGORITHM  ->  CODE  ->  DRY RUN  ->  VIVA
```

This guide teaches you all five, in that order, for each assignment.

---

## 1. Your assignment map

| # | Assignment | Files | Chapter |
|---|------------|-------|---------|
| 1 | Matrix add / subtract / multiply / transpose | `ass1.c` | `02_MATRIX.md` |
| 2 | Saddle point of a matrix | `saddle_point.c` | `02_MATRIX.md` |
| 3 | Linear search and binary search | `linear_search.c`, `binary_search.c`, `Searching_sorting.c` | `03_SEARCHING.md` |
| 4 | Bubble, selection, insertion, shell sort | `bubble_sort.c`, `selection_sort.c`, `Searching_sorting.c` | `04_SORTING.md` |
| 5 | Sparse matrix: triplet form, transpose, addition | `sparse_matrix.c`, `simple_trans.c`, `fast_trans.c`, `combi_sparse.c`, `sparse_add.c` | `05_SPARSE.md` |
| 6 | Stack: infix to postfix, postfix evaluation | `stack.c`, `stack2.c` | `06_STACK.md` |
| 7 | Linear queue | `linear_queue.c` | `07_QUEUE.md` |
| 8 | Circular queue | `circular_queue.c` | `07_QUEUE.md` |
| 9 | Singly linked list (workshop enrollment) | `singlyll.c` | `08_SLL.md` |
| 10 | Circular linked list + polynomial addition | `circlell.c`, `poly_add.c`, `poly_add_menu.c` | `09_CLL_POLY.md` |

Support material:

- `01_C_PRIMER.md` — the only C you need. Read this first if pointers scare you.
- `10_VIVA_EXPRESS.md` — 120 rapid-fire viva questions with one-line answers.
- `11_CHEATSHEET.md` — print this. Read it the morning of the exam.

---

## 2. How the 40 marks are usually split

Most university practical externals look like this (ask your teacher to confirm):

| Part | What you do | Typical marks |
|------|-------------|---------------|
| A | Write the **algorithm** for a given problem | 10 |
| B | Write the **C program** | 15–20 |
| C | Show **output / dry run** | 5 |
| D | **Viva** (oral questions) | 5–10 |

The single most common reason students lose marks is **not** bad code. It is:

1. Algorithm written in C syntax instead of plain steps.
2. Forgetting `Start` / `Stop` or the loop `end for` lines.
3. Not initialising (e.g. `sum = 0`, `top = -1`, `front = rear = -1`).
4. Off-by-one errors in loops.
5. Not being able to explain their own code in viva.

---

## 3. How to write an algorithm that gets full marks

An examiner is not checking whether your algorithm looks pretty. They are checking five things:

1. **Correct input / output written at the top.**
2. **Numbered steps** that always begin with `Step 1: Start`.
3. **Every loop has an `end for` / `end while`.**
4. **Every `if` has an `end if`.**
5. **A clear `Stop` at the end.**

### The universal template

```
Algorithm: <Name of algorithm>
Input : <what is given, with sizes>
Output: <what is produced>

Step 1: Start
Step 2: <initialisation>
Step 3: for i = 0 to n-1 do
Step 4:     <body>
Step 5: end for
Step 6: <final action>
Step 7: Stop
```

Write it **without semicolons and without `int i;`** — that is code, not an algorithm.
Index variables do not need declaration. Use words like `do`, `end for`, `if ... then ... else`.

### Example you can copy the style from

**Algorithm: Linear Search**

```
Algorithm: LinearSearch(A, n, key)
Input : Array A of n elements, and the key to search
Output: Position of key if found, otherwise -1

Step 1: Start
Step 2: for i = 0 to n-1 do
Step 3:     if A[i] = key then
Step 4:         return i
Step 5:     end if
Step 6: end for
Step 7: return -1
Step 8: Stop
```

That is a 10/10 answer. Short, numbered, complete.

### If they ask for complexity, add one line

```
Time Complexity : O(n)   [best case O(1), worst case O(n)]
Space Complexity: O(1)
```

One line. That is usually worth 1–2 marks and takes 10 seconds.

---

## 4. How to write the program that gets full marks

Use this skeleton for **every** menu-driven assignment. It is the same in all your files.

```c
#include <stdio.h>
#include <stdlib.h>     /* malloc, free, exit */

#define MAX 100

/* 1. global variables / stack / queue  */
/* 2. struct definitions                */
/* 3. function definitions              */
/* 4. main() with do-while + switch     */

int main()
{
    int choice;

    do
    {
        printf("\n1. ...\n2. ...\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: /* call function */ break;
        case 2: /* call function */ break;
        case 3: printf("Exiting...\n"); break;
        default: printf("Invalid choice\n");
        }
    } while (choice != 3);

    return 0;
}
```

**What the examiner looks for, in order:**

| Check | Marks |
|-------|-------|
| `#include` lines and `main()` present | 1 |
| Variables declared, initialised | 1 |
| Correct logic | most of the marks |
| Loops closed properly, braces matched | 1 |
| `printf`/`scanf` sensible, output readable | 1 |
| `return 0;` | 1 |

If you get stuck mid-program: **write the function signatures, write `main()` with the
menu, and leave the logic as comments.** A structured half-answer scores far more than
a blank page.

---

## 5. Compile and run (Windows, your machine)

You already have GCC 6.3 installed. From this folder:

```powershell
gcc ass1.c -o ass1 -Wall
.\ass1.exe
```

- `-Wall` turns on warnings. **Read them** — they usually point at a real bug.
- `-o name` names the output file.
- To compile with the interactive prompts in the template files:
  `gcc -DINTERACTIVE poly_add_menu.c -o poly -Wall`

**Exam tip:** if the machine has no compiler and they ask you to write on paper,
write code exactly as if it will compile. Do not invent syntax.

---

## 6. A 7-day plan (2 hours a day)

| Day | What to do | Chapter |
|-----|-----------|---------|
| 1 | C primer: arrays, functions, pointers, structs, `malloc` | `01_C_PRIMER.md` |
| 2 | Matrix + saddle point. Write both algorithms from memory. | `02_MATRIX.md` |
| 3 | Searching + sorting. Memorise the 4 sort algorithms. | `03`, `04` |
| 4 | Sparse matrix: triplet, simple transpose, fast transpose, addition. | `05_SPARSE.md` |
| 5 | Stack + queue (linear and circular). Trace by hand. | `06`, `07` |
| 6 | Linked lists: singly + circular + polynomial. Draw boxes and arrows. | `08`, `09` |
| 7 | Viva bank + cheat sheet + one full mock answer on paper. | `10`, `11` |

If you only have **one day**: read `11_CHEATSHEET.md`, then memorise the four
algorithms marked `[MEMORISE]` in the chapters (binary search, bubble sort,
infix-to-postfix, linked-list reverse).

---

## 7. How to use each chapter

Every chapter has the same sections:

- **The idea** — plain English, no jargon.
- **Picture** — a diagram so you can *see* the data structure.
- **Algorithm `[MEMORISE]`** — exactly what to write in Part A.
- **The code** — a walkthrough of *your* file, function by function.
- **Dry run** — a table you can reproduce in Part C.
- **Viva** — the questions actually asked, with short answers.
- **Traps** — the marks students lose here.

---

## 8. Ten golden rules for the lab exam

1. **Read the question twice.** Underline the data structure and the operation.
2. Start the algorithm with `Start`, end with `Stop`.
3. Initialise every counter and pointer: `top = -1`, `front = rear = -1`, `head = NULL`.
4. In C, array indices go `0 .. n-1`. Write `i < n`, not `i <= n`.
5. A `for` loop with `n` elements does `n` iterations, but bubble/selection sort
   outer loop is `n-1` because the last element is already in place.
6. Draw the linked list on paper before coding. It prevents 80% of pointer bugs.
7. After `malloc`, always check `if (newNode == NULL)`.
8. Every `malloc` should have a matching `free` somewhere before exit.
9. If code fails, **do not panic and rewrite**. Print intermediate values
   (`printf("top=%d\n", top);`) and find the first wrong value.
10. In viva, if you don't know: say what you *do* know, then say "I haven't covered
    that yet." Never invent. Examiners forgive gaps, not bluffing.

---

## 9. The one sentence that explains DSA

> An **array** is a row of numbered boxes. A **linked list** is a chain of boxes where
> each box holds the address of the next. A **stack** is a pile you add to and remove
> from the top. A **queue** is a line where you join at the back and leave from the
> front. Everything else is a variation on those four ideas.

Keep that sentence in your head and the viva becomes much easier.

---

**Next:** open `01_C_PRIMER.md`.
