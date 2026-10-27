# 02 — Matrix Operations & Saddle Point

**Files:** `ass1.c`, `saddle_point.c`
**Exam value:** usually the easiest full-marks question. Pure nested loops.

---

# Part A — Matrix addition, subtraction, multiplication, transpose
scanf("%d", n)
    int n = 10;
## The idea

A matrix is just a **2D array**. Every operation is "visit each cell and compute
something". The only operation with a twist is multiplication.

| Operation | Rule | Loops |
|-----------|------|-------|
| Addition | `C[i][j] = A[i][j] + B[i][j]` | 2 |
| Subtraction | `C[i][j] = A[i][j] - B[i][j]` | 2 |
| Multiplication | `C[i][j] = Σ A[i][k] * B[k][j]` | 3 |
| Transpose | `T[j][i] = A[i][j]` | 2 |

**Preconditions — write these in the exam:**

- Addition / subtraction: both matrices must have the **same order** `m × n`.
- Multiplication: **columns of A must equal rows of B**. If A is `m×n` and B is `n×p`,
  result is `m×p`.
- A square matrix `n×n` can be transposed in place; otherwise you need a second array.

---

## Matrix addition `[MEMORISE]`

```
Algorithm: MatrixAddition(A, B, m, n)
Input : Two matrices A and B, each of order m x n
Output: Matrix C = A + B

Step 1: Start
Step 2: for i = 0 to m-1 do
Step 3:     for j = 0 to n-1 do
Step 4:         C[i][j] = A[i][j] + B[i][j]
Step 5:     end for
Step 6: end for
Step 7: Display C
Step 8: Stop
```

**Time:** O(m·n). **Space:** O(m·n) for the result (O(1) extra if you print directly).

Subtraction is identical with `-`.

---

## Matrix multiplication `[MEMORISE]`

This is the one students get wrong. Learn the **i–j–k order**:

```
        A (m x n)          B (n x p)              C (m x p)
     +---+---+---+      +---+---+              +---+---+
     |   |   |   |      |   |   |              |   |   |
     +---+---+---+  x   +---+---+   =          +---+---+
     |   |   |   |      |   |   |              |   |   |
     +---+---+---+      +---+---+              +---+---+
```

`C[i][j]` = dot product of **row i of A** and **column j of B**.

```
C[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0] + A[1][2]*B[2][0]
          └────────── row 1 of A ──────────┘   └─ column 0 of B ─┘
```

```
Algorithm: MatrixMultiplication(A, B, C, m, n, p)
Input : Matrix A of order m x n, matrix B of order n x p
Output: Matrix C of order m x p, where C = A x B

Step 1: Start
Step 2: for i = 0 to m-1 do
Step 3:     for j = 0 to p-1 do
Step 4:         C[i][j] = 0
Step 5:         for k = 0 to n-1 do
Step 6:             C[i][j] = C[i][j] + A[i][k] * B[k][j]
Step 7:         end for
Step 8:     end for
Step 9: end for
Step 10: Display C
Step 11: Stop
```

**Time:** O(m·n·p); for `n×n` matrices, **O(n³)**.
**Space:** O(m·p) for the result.

### Trace: 2 × 2

```
A = | 1 2 |     B = | 5 6 |
    | 3 4 |         | 7 8 |

C[0][0] = 1*5 + 2*7 = 5 + 14 = 19
C[0][1] = 1*6 + 2*8 = 6 + 16 = 22
C[1][0] = 3*5 + 4*7 = 15 + 28 = 43
C[1][1] = 3*6 + 4*8 = 18 + 32 = 50
```

| i | j | k | C[i][j] after step 6 |
|---|---|----|----------------------|
| 0 | 0 | 0 | 5 |
| 0 | 0 | 1 | 19 |
| 0 | 1 | 0 | 6 |
| 0 | 1 | 1 | 22 |
| 1 | 0 | 0 | 15 |
| 1 | 0 | 1 | 43 |
| 1 | 1 | 0 | 18 |
| 1 | 1 | 1 | 50 |

### The fix in your `ass1.c`

Your original `mul()` computed:

```c
c[i][j] = a[i][j] * b[i][j];      /* element-wise, NOT matrix multiplication */
```

and printed **"Element-wise Multiplication"**. That is the *Hadamard product*, a valid
operation, but **it is not what "matrix multiplication" means in an exam**. If the
question says *multiply two matrices*, you must use the three-loop version. That inner
loop is the **only** change made to your file; the rest of the layout is untouched.

Because `ass1.c` uses a fixed 3×3 matrix, `m == n`, so the `k` loop simply runs to `n`:

```c
void mul(int a[10][10], int b[10][10], int c[10][10], int m, int n)
{
    printf("\nEnter elements of Second Matrix:\n");
    accept(b, m, n);

    printf("\nMultiplication of Matrices:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = 0;                        /* MUST initialise */

            for (int k = 0; k < n; k++)
            {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }

            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}
```

Keep the distinction for viva: element-wise product is used in image processing, but
"matrix multiplication" means rows × columns. Only use the one-line version if the
question explicitly says *element-wise*.

Exam version with **non-square** matrices (extra `p` for B's columns) — only if the
question does not fix the order:

```c
void multiply(int a[10][10], int b[10][10], int c[10][10],
              int m, int n, int p)
{
    int i, j, k;

    for (i = 0; i < m; i++)
        for (j = 0; j < p; j++)
        {
            c[i][j] = 0;                        /* MUST initialise */
            for (k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
}
```

**Almost everyone forgets `c[i][j] = 0;`** → the sum starts from garbage. That one line
is a mark.

**Memory hook:** `i` picks the **row of A**, `j` picks the **column of B**, `k` walks
**across the row / down the column** doing the multiply-add.

---

## Transpose `[MEMORISE]`

Transpose = swap rows and columns. `T[j][i] = A[i][j]`.

```
A (2 x 3)              T (3 x 2)
1 2 3                  1 4
4 5 6                  2 5
                       3 6
```

```
Algorithm: Transpose(A, m, n)
Input : Matrix A of order m x n
Output: Matrix T of order n x m

Step 1: Start
Step 2: for i = 0 to m-1 do
Step 3:     for j = 0 to n-1 do
Step 4:         T[j][i] = A[i][j]
Step 5:     end for
Step 6: end for
Step 7: Display T with n rows and m columns
Step 8: Stop
```

**Time:** O(m·n). **Space:** O(m·n) extra.

### Trap
When printing the transpose, the loops must be `for i < n` (rows) and `for j < m`
(columns), because the result has **swapped dimensions**. Your `ass1.c` does this
correctly (lines 101–108).

### In-place transpose for a square matrix (bonus viva answer)

```c
for (i = 0; i < n; i++)
    for (j = i + 1; j < n; j++)   /* j starts at i+1: only above the diagonal */
    {
        temp = a[i][j];
        a[i][j] = a[j][i];
        a[j][i] = temp;
    }
```

Starting `j` at `i+1` avoids swapping every pair twice (which would undo the transpose).

---

## How `ass1.c` is organised (line-by-line map)

| Lines | Function | Does |
|-------|----------|------|
| 4–14 | `accept` | reads `m×n` values into a matrix |
| 16–28 | `display` | prints the matrix |
| 30–45 | `add` | reads B, computes and prints A+B |
| 47–62 | `subtract` | reads B, computes and prints A−B |
| 64–85 | `mul` | true product with three loops (`k` runs to `n` because it is 3×3) |
| 87–109 | `trans` | stores `temp[j][i] = a[i][j]`, then prints `n×m` |
| 111–158 | `main` | fixed 3×3, reads A, menu, `switch` |

**Structure lesson:** `accept`/`display` are reused by every operation. That is good
design and worth mentioning in viva: *"I separated input/output from computation so the
same functions can be reused."*

**Only one thing changed:** the element-wise `c[i][j] = a[i][j] * b[i][j]` became the
three-loop sum, and the heading now says "Multiplication of Matrices". The file is
still the short single-run version: 3×3, one operation per run, B read inside the
chosen function. That is the version to rehearse for the exam.

**If the question fixes the order at 3×3**, keep it this way — fewer variables, less to
explain. Only add `p` and general dimensions if the question asks for non-square
matrices.

---

## Viva — matrices

**Q1. What is a matrix?**
A two-dimensional array of `m` rows and `n` columns, where an element is accessed as
`A[i][j]`.

**Q2. How is a 2D array stored in memory?**
In **row-major order**: all of row 0, then all of row 1, and so on. Address of `A[i][j]`
is `base + (i * columns + j) * sizeof(type)`.

**Q3. Condition for matrix addition?**
Both matrices must have the same order `m × n`.

**Q4. Condition for matrix multiplication?**
Number of **columns of A** must equal number of **rows of B**
(`A[m][n] × B[n][p] → C[m][p]`).

**Q5. Is matrix multiplication commutative?**
No. `AB ≠ BA` in general, and `BA` may not even be defined.

**Q6. Complexity of matrix multiplication?**
O(m·n·p), or **O(n³)** for square matrices. (Strassen's algorithm is about O(n^2.81);
not required, but a nice bonus answer.)

**Q7. Why is `c[i][j] = 0` needed before the k loop?**
Because we accumulate with `+=`; without initialising, C adds to whatever garbage was in
that memory.

**Q8. What is transpose?**
The matrix obtained by interchanging rows and columns: `T[j][i] = A[i][j]`. Order changes
from `m×n` to `n×m`.

**Q9. Is `(Aᵀ)ᵀ = A`?**
Yes. Transposing twice returns the original.

**Q10. What is a symmetric matrix?**
A square matrix equal to its transpose, i.e. `A[i][j] = A[j][i]`.

**Q11. What is the identity matrix?**
A square matrix with 1s on the main diagonal and 0 elsewhere; `A·I = A`.

**Q12. What is a sparse matrix?**
A matrix in which most elements are zero. (More in `05_SPARSE.md`.)

---

# Part B — Saddle point

## The idea

A **saddle point** is an element that is:

- the **smallest in its row**, AND
- the **largest in its column**.

Like the lowest point of a mountain pass: low along the ridge, high across the valley.

```
       col0  col1  col2
row0 |  1     2     3
row1 |  4     5     6
row2 |  7     8     9
```

- Row 0 minimum = 1 (col 0). Is 1 the maximum of column 0? Column 0 = {1,4,7}, max = 7.
  No.
- Row 1 minimum = 4 (col 0). Column 0 max = 7. No.
- Row 2 minimum = 7 (col 0). Column 0 max = 7. **Yes → saddle point = 7 at (2,0).**

There may be zero, one, or several saddle points.

## Algorithm `[MEMORISE]`

```
Algorithm: SaddlePoint(A, m, n)
Input : Matrix A of order m x n
Output: Saddle point(s) with position, or a message if none

Step 1: Start
Step 2: found = 0
Step 3: for i = 0 to m-1 do
Step 4:     min = A[i][0], col = 0
Step 5:     for j = 1 to n-1 do
Step 6:         if A[i][j] < min then
Step 7:             min = A[i][j], col = j
Step 8:         end if
Step 9:     end for
Step 10:    flag = 1
Step 11:    for k = 0 to m-1 do
Step 12:        if A[k][col] > min then
Step 13:            flag = 0
Step 14:        end if
Step 15:    end for
Step 16:    if flag = 1 then
Step 17:        print min and position (i, col)
Step 18:        found = 1
Step 19:    end if
Step 20: end for
Step 21: if found = 0 then print "No saddle point"
Step 22: Stop
```

**Time:** O(m·n + m²) — for each of the `m` rows we scan the row (n) and then its column
(m). For an `n × n` matrix that is O(n²).

## How your `saddle_point.c` does it

| Lines | What |
|-------|------|
| 9–24 | read rows `m`, columns `n`, and the matrix |
| 26–35 | display the matrix |
| 37–49 | for each row, find its minimum and remember `col` |
| 51–58 | scan column `col`; `break` as soon as a bigger value is found |
| 60–65 | if the loop ran fully (`k == m`), it is the column maximum → saddle point |
| 68–71 | if none found, print the message |

The trick on lines 51–58 is worth understanding: `break` exits the loop early, so if no
break happened, `k` ends at `m`. That is a common C idiom for "no exception found".

## Dry run

```
Matrix:   1  2  3
          4  5  6
          7  8  9

i=0: min=1, col=0 → column 0 = {1,4,7}, 7 > 1 → break → not a saddle point
i=1: min=4, col=0 → 7 > 4 → break            → not a saddle point
i=2: min=7, col=0 → no value > 7 → k reaches m → SADDLE POINT 7 at (2,0)
```

## Limitation (mention this for extra marks)

If a row contains the **same minimum value more than once**, the program only checks the
first occurrence, because `if (mat[i][j] < min)` uses `<` rather than `<=` and records
one `col`. A fully general solution checks every column whose value equals the row
minimum. Most exam answers ignore this; saying it out loud shows depth.

---

## Viva — saddle point

**Q1. Define saddle point.**
An element that is the minimum of its row and the maximum of its column.

**Q2. Can there be more than one saddle point?**
Yes. A matrix can have several, or none.

**Q3. Can two saddle points have the same value?**
Yes — different rows can each produce the same value.

**Q4. Complexity of your algorithm?**
O(m·n) for an `m×n` matrix.

**Q5. What does `break` do here?**
It exits the inner column loop immediately when a larger element is found, since the
candidate can no longer be the column maximum.

**Q6. How do you know the loop finished without breaking?**
Check whether the loop counter reached the limit (`k == m`).

---

## Traps checklist

- [ ] Initialised `C[i][j] = 0` before the `k` loop.
- [ ] Three loops in the order **i, j, k** for multiplication.
- [ ] Transpose result printed with loops `n` rows, `m` columns.
- [ ] Loops use `<`, not `<=`.
- [ ] Declared the correct dimensions (`A[m][n]`, `B[n][p]`, `C[m][p]`).
- [ ] `found` flag initialised to 0.

---

**Next:** `03_SEARCHING.md`
