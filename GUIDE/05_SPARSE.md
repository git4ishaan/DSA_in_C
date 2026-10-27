# 05 - Sparse Matrix: Triplet and Transpose

**Program:** `combi_sparse.c`

This program reads one matrix and, in one run, displays:

1. the original matrix;
2. its sparse triplet representation;
3. its simple transpose in triplet form; and
4. its fast transpose in triplet form.

There is no menu: all four outputs are produced automatically after input.

## Triplet representation

A sparse matrix has mostly zero values. `combi_sparse.c` stores only its non-zero
values in a three-column array:

| Triplet row | Contents |
| --- | --- |
| `b[0]` | `(number of rows, number of columns, number of non-zero values)` |
| `b[1]` to `b[t]` | `(row, column, value)` for each non-zero value |

For example:

```text
0 0 3 0
0 0 0 0
5 0 0 0
0 0 0 7
```

becomes:

```text
Row  Col  Value
4    4    3
0    2    3
2    0    5
3    3    7
```

The first row is the header. The remaining rows are non-zero matrix entries,
stored in row-major order because `sparse()` scans the original matrix row by row.

## Program flow

```text
accept()
  -> displayMatrix()
  -> sparse()
  -> displayTriplet()
  -> simpleTranspose()
  -> displayTriplet()
  -> fastTranspose()
  -> displayTriplet()
```

| Function | Purpose |
| --- | --- |
| `accept()` | Reads the original matrix. |
| `displayMatrix()` | Prints the original matrix. |
| `sparse()` | Builds the compact triplet array. |
| `displayTriplet()` | Prints a triplet array, including its header. |
| `simpleTranspose()` | Transposes by scanning all triplets once per original column. |
| `fastTranspose()` | Transposes using counts and starting positions. |

## Simple transpose

For a transpose, each element at `(row, col)` moves to `(col, row)`. Therefore an
`m x n` matrix becomes an `n x m` matrix.

`simpleTranspose()` first swaps the dimensions in the header:

```c
b[0][0] = a[0][1];
b[0][1] = a[0][0];
b[0][2] = a[0][2];
```

It then loops through the original columns. For each column, it scans every
non-zero triplet and copies matching entries with their row and column exchanged.

```text
for each original column
    for each non-zero triplet
        if its column is the current column
            write (column, row, value)
```

Time complexity: **O(n x t)**, where `n` is the original column count and `t` is
the number of non-zero elements.

## Fast transpose

`fastTranspose()` avoids repeatedly scanning the full triplet list. It uses:

- `rowTerms[col]` to count non-zero entries in each original column;
- `startPos[col]` to hold the next free row for that column in the transpose.

The steps are:

```text
1. Count terms in each original column.
2. Calculate each transpose row's initial position.
3. For every triplet (row, col, value):
   write (col, row, value) at startPos[col], then increment startPos[col].
```

`startPos[0]` is `1`, rather than `0`, because row `0` is reserved for the
triplet header.

For the example matrix:

```text
rowTerms = [1, 0, 1, 1]
startPos = [1, 2, 2, 3]
```

Both transpose methods produce:

```text
Row  Col  Value
4    4    3
0    2    5
2    0    3
3    3    7
```

Time complexity: **O(n + t)**. Extra space: **O(n)**.

## Example input

```text
Enter number of rows: 4
Enter number of columns: 4

Enter Matrix Elements:
Element[0][0]: 0
Element[0][1]: 0
Element[0][2]: 3
Element[0][3]: 0
Element[1][0]: 0
Element[1][1]: 0
Element[1][2]: 0
Element[1][3]: 0
Element[2][0]: 5
Element[2][1]: 0
Element[2][2]: 0
Element[2][3]: 0
Element[3][0]: 0
Element[3][1]: 0
Element[3][2]: 0
Element[3][3]: 7
```

## Current implementation limit

The original matrix is `matrix[10][10]`, so it supports at most 10 rows and 10
columns. However, each triplet array is only `int[20][3]`: one header plus 19
non-zero entries. A matrix with 20 or more non-zero values writes past that array.
Use inputs with at most 19 non-zero values until the program is updated to increase
the triplet capacity or validate the count.

Compile and run:

```powershell
gcc -std=c99 -Wall -Wextra combi_sparse.c -o combi_sparse
.\combi_sparse.exe
```

## Viva quick answers

**What does the header store?** The original row count, column count, and number
of non-zero values.

**Why swap row and column?** Transposition maps `(i, j)` to `(j, i)`.

**Why is fast transpose faster?** It finds each destination position directly,
so it runs in O(n + t) instead of O(n x t).

**Why does `startPos[0]` begin at 1?** Index 0 is the header, not a data term.

**Next:** `06_STACK.md`
