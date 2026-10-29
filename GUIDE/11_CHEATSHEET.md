# 11 — Night-Before Cheat Sheet

Print this. Read it in the exam hall corridor. Everything here is worth marks.

---

## 0. The exam routine

1. Read the question twice; underline the data structure and the operation.
2. Write **Algorithm** with `Start` … `Stop`, numbered steps, `end for` / `end if`.
3. Add one line: `Time Complexity: O(...)`.
4. Write the **program** with includes, `#define`, struct, functions, `main`.
5. Trace one small example in a table for the **output** marks.
6. Before viva, re-read your own code.

---

## 1. Universal C skeleton

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main()
{
    int choice;
    do
    {
        printf("\n1. Insert\n2. Delete\n3. Display\n4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: /* ... */ break;
        case 2: /* ... */ break;
        case 3: /* ... */ break;
        case 4: printf("Exit\n"); break;
        default: printf("Invalid\n");
        }
    } while (choice != 4);

    return 0;
}
```

---

## 2. The algorithms, compressed

### Matrix multiplication
```
for i = 0 to m-1
  for j = 0 to p-1
    C[i][j] = 0
    for k = 0 to n-1
      C[i][j] = C[i][j] + A[i][k] * B[k][j]
```

### Transpose
```
for i = 0 to m-1
  for j = 0 to n-1
    T[j][i] = A[i][j]
```

### Saddle point
```
for each row i
  find min in row i, remember its column c
  if min is the maximum of column c  ->  saddle point
```

### Linear search
```
for i = 0 to n-1
  if A[i] = key  ->  return i
return -1
```

### Binary search
```
low = 0, high = n-1
while low <= high
  mid = (low + high) / 2
  if A[mid] = key   -> return mid
  if A[mid] < key   -> low = mid + 1
  else              -> high = mid - 1
return -1
```

### Bubble sort
```
for i = 0 to n-2
  for j = 0 to n-2-i
    if A[j] > A[j+1]  -> swap
```

### Selection sort
```
for i = 0 to n-2
  min = i
  for j = i+1 to n-1
    if A[j] < A[min]  -> min = j
  swap A[i], A[min]
```

### Insertion sort
```
for i = 1 to n-1
  key = A[i], j = i-1
  while j >= 0 and A[j] > key
    A[j+1] = A[j], j = j-1
  A[j+1] = key
```

### Shell sort
```
gap = n/2
while gap > 0
  for i = gap to n-1
    temp = A[i], j = i
    while j >= gap and A[j-gap] > temp
      A[j] = A[j-gap], j = j-gap
    A[j] = temp
  gap = gap/2
```

### Sparse: matrix → triplets
```
k = 1
for i = 0 to m-1
  for j = 0 to n-1
    if A[i][j] != 0
      S[k] = (i, j, A[i][j]); k++
S[0] = (m, n, k-1)
```

### Sparse: simple transpose
```
B[0] = (A[0][1], A[0][0], A[0][2]); k = 1
for c = 0 to A[0][1]-1
  for p = 1 to A[0][2]
    if A[p][1] = c
      B[k] = (A[p][1], A[p][0], A[p][2]); k++
```

### Sparse: fast transpose
```
B[0] = (A[0][1], A[0][0], A[0][2])
rowTerms[0..cols-1] = 0
for i = 1 to t
  rowTerms[A[i][1]]++
startPos[0] = 1
for i = 1 to cols-1
  startPos[i] = startPos[i-1] + rowTerms[i-1]
for i = 1 to t
  j = startPos[A[i][1]]
  B[j] = (A[i][1], A[i][0], A[i][2])
  startPos[A[i][1]]++
```

### Sparse addition
```
if dimensions differ -> error
i = j = k = 1
while i <= tA and j <= tB
  if A[i].pos = B[j].pos      -> C[k] = sum, i++, j++
  else if A[i].pos < B[j].pos -> C[k] = A[i], i++
  else                        -> C[k] = B[j], j++
  k++          (skip if the sum is 0)
copy the remaining terms
```

### Stack: push / pop
```
push: if top = MAX-1 -> overflow
      else top++, S[top] = x

pop:  if top = -1 -> underflow
      else x = S[top], top--
```

### Infix → postfix
```
for each ch
  operand  -> output
  '('      -> push
  ')'      -> pop+output until '('; discard '('
  operator -> pop+output while prec(top) >= prec(ch); push ch
pop+output everything remaining
```

### Evaluate postfix
```go through the files and 

Update the content as i have implemented many changes
for each ch
  digit    -> push value
  operator -> b = pop, a = pop, push (a op b)
answer = pop
```

### Queue (linear)
```
enqueue: if rear = MAX-1 -> overflow
         if front = -1 -> front = 0
         rear++, Q[rear] = x

dequeue: if front = -1 -> underflow
         x = Q[front], front++
         if front > rear -> front = rear = -1
```

### Circular queue
```
full  : (rear + 1) % MAX = front
enqueue: if front = -1 -> front = rear = 0
         else rear = (rear + 1) % MAX
         Q[rear] = x
dequeue: if front = rear -> front = rear = -1
         else front = (front + 1) % MAX
```

### Singly linked list
```
insert at end:
  new->next = NULL
  if head = NULL -> head = new
  else temp = head; while temp->next != NULL -> temp = temp->next
       temp->next = new

delete key:
  temp = head, prev = NULL
  while temp != NULL and temp->data != key -> prev = temp, temp = temp->next
  if temp = NULL -> not found
  else if prev = NULL -> head = temp->next
  else prev->next = temp->next
  free(temp)

reverse:
  prev = NULL, curr = head
  while curr != NULL
    next = curr->next
    curr->next = prev
    prev = curr
    curr = next
  head = prev

traverse:
  temp = head; while temp != NULL -> visit, temp = temp->next
```

### Circular linked list
```
traverse:
  p = head
  do { visit p; p = p->next; } while (p != head)
```

### Polynomial addition
```
p = P1 head, q = P2 head
while both have terms
  if exps equal   -> insert (p.coef + q.coef, exp) if non-zero; advance both
  else if p.exp > q.exp -> insert p; advance p
  else                   -> insert q; advance q
copy remaining terms
```

---

## 3. Complexity table

| Algorithm / operation | Best | Average | Worst | Space | Stable |
|---|---|---|---|---|---|
| Linear search | O(1) | O(n) | O(n) | O(1) | — |
| Binary search | O(1) | O(log n) | O(log n) | O(1) | — |
| Bubble sort | O(n)* | O(n²) | O(n²) | O(1) | Yes |
| Selection sort | O(n²) | O(n²) | O(n²) | O(1) | No |
| Insertion sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Shell sort | O(n log n) | ~O(n^1.3) | O(n²) | O(1) | No |
| Matrix add / transpose | — | — | O(m·n) | O(m·n) | — |
| Matrix multiply | — | — | O(m·n·p) | O(m·p) | — |
| Sparse simple transpose | — | — | O(cols × t) | O(t) | — |
| Sparse fast transpose | — | — | O(cols + t) | O(cols) | — |
| Sparse addition | — | — | O(t1 + t2) | O(t1 + t2) | — |
| Push / pop / enqueue / dequeue | — | — | O(1) | O(1) | — |
| Infix→postfix / postfix eval | — | — | O(n) | O(n) | — |
| List insert at front | — | — | O(1) | O(1) | — |
| List insert at end | — | — | O(n) | O(1) | — |
| List search / count / traverse | — | — | O(n) | O(1) | — |
| List reverse | — | — | O(n) | O(1) | — |
| Polynomial addition (merge) | — | — | O(m+n) | O(m+n) | — |

\* with the early-exit flag.

---

## 4. C gotchas that cost marks

| Mistake | Fix |
|---|---|
| `scanf("%d", n)` | `scanf("%d", &n)` |
| `for (i = 0; i <= n; i++)` on an array | `i < n` |
| `c[i][j] += ...` without initialising | `c[i][j] = 0;` first |
| `free(p); p->next` | save `next` before `free` |
| `if (s1 == s2)` for strings | `strcmp(s1, s2) == 0` |
| `p.` on a pointer | `p->` |
| `malloc` without a NULL check | `if (p == NULL) return;` |
| `scanf("%s", name)` for a full name | `scanf(" %49[^\n]", name)` |
| forgetting `p = p->next` | infinite loop |
| forgetting `break` in `switch` | fall-through |
| algorithm written in C syntax | plain numbered steps |
| no `Stop` at the end | add it |
| `top`/`front`/`rear` not initialised | `-1` |

---

## 5. Definitions in one line each

- **Data structure** — a way of organising data in memory for efficient use.
- **Algorithm** — a finite sequence of steps that solves a problem.
- **Stack** — LIFO, insert/delete at the top.
- **Queue** — FIFO, insert at rear, delete at front.
- **Circular queue** — a queue whose indices wrap using modulo, reusing freed slots.
- **Linked list** — nodes in scattered memory linked by pointers.
- **Circular linked list** — last node points back to the first.
- **Sparse matrix** — a matrix with mostly zeros.
- **Triplet** — `(row, column, value)` of one non-zero element.
- **Stable sort** — equal elements keep their original order.
- **In-place** — O(1) extra memory.
- **Overflow** — inserting into a full structure.
- **Underflow** — deleting from an empty structure.
- **Dangling pointer** — points to freed memory.
- **Memory leak** — allocated memory never freed.

---

## 6. Traps by data structure

| Structure | The one thing to remember |
|---|---|
| Matrix | `C[i][j] = 0` before the k loop; result of `m×n · n×p` is `m×p` |
| Saddle point | min in row, max in column; `found` flag starts at 0 |
| Searching | binary needs sorted data; `low <= high` |
| Sorting | outer loop `n-1`; `j+1` must stay in bounds |
| Sparse | header row; `k` starts at 1; fast transpose = count → prefix → place |
| Stack | `top = -1`; pop right operand first in evaluation |
| Queue | circular full test `(rear+1)%MAX == front`; display wraps |
| Linked list | save `next` before changing links; handle the head case |
| Circular list | stop at `head`, not `NULL`; `p == head` is ambiguous, use `prev` |
| Polynomial | keep descending order; combine equal exponents; drop zeros |

---

## 7. If you only have 30 minutes left

Memorise these five, in this order:

1. **Binary search** — 8 lines, guaranteed question.
2. **Bubble sort** — 5 lines, easiest sorting marks.
3. **Infix → postfix** — the 4-case loop.
4. **Linked list insert + delete + reverse** — the three pointer patterns.
5. **Circular queue enqueue/dequeue** — the modulo formulas.

Then read the definition list above and the "one thing to remember" table.

---

Good luck. You know more than you think — write the algorithm first, keep the code simple,
and explain what you wrote.
