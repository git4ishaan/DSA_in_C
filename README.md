# DS Lab work

C implementations of Data Structures & Algorithms, written while learning.

## Programs

| File | Topic |
|------|-------|
| `Matrix_Operations.c` | Matrix add / subtract / multiply / transpose |
| `Searching_sorting.c` | Linear & binary search, insertion / selection / shell sort |
| `bubble_sort.c` | Bubble sort |
| `combi_sparse.c` | Sparse matrix: triplet form, simple & fast transpose |
| `stack.c`, `stack2.c` | Stack (infix→postfix, postfix evaluation) |
| `linear_queue.c`, `linear_queue_simple.c` | Linear queue (print-job records / plain integers) |
| `circular_queue.c`, `circular_queue_simple.c` | Circular queue (print-job records / plain integers) |
| `singlyll.c` | Singly linked list (workshop enrollment) |
| `circlell.c`, `poly_add.c`, `poly_add_menu.c` | Circular list + polynomial addition |

There are **14 programs** covering **9 assignments**. The `_simple` queue files are the
minimal integer versions; the other two show the same operations on a queue of structs.

## Documentation

- [`ALL_CODE.md`](ALL_CODE.md) — every program in one place, copied exactly from the
  `.c` files.
- [`GUIDE/`](GUIDE/) — exam-oriented notes for every assignment: concept, exam-ready
  algorithm, annotated code, dry run, viva questions and common mistakes.

Start at [`GUIDE/00_START_HERE.md`](GUIDE/00_START_HERE.md).

## Build

```powershell
gcc Matrix_Operations.c -o matrix_operations -Wall
.\matrix_operations.exe
```

Replace the file name with any program from the table above. For the interactive
polynomial program, add `-DINTERACTIVE`:

```powershell
gcc -DINTERACTIVE poly_add_menu.c -o poly_add_menu -Wall
```
