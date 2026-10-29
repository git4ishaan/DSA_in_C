# 09 — Circular Linked List & Polynomial Addition

**Files:** `circlell.c`, `poly_add.c`, `poly_add_menu.c`
**Exam value:** high. "Represent a polynomial using a linked list and add two polynomials"
is a standard 10–15 mark question.

---

# Part A — Circular linked list

## The idea

A singly linked list where the **last node points back to the first** instead of `NULL`.

```
        +-----------------------------------+
        |                                   |
        v                                   |
     +----+---+    +----+---+    +----+---++
     | 10 | *-+--> | 20 | *-+--> | 30 | *  |
     +----+---+    +----+---+    +----+---+
       ^head
```

There is no `NULL` anywhere. The list is a **ring**.

**How do you know you've reached the end?** When you come back to `head`.

```c
if (head != NULL)
{
    p = head;
    do
    {
        /* process p */
        p = p->next;
    } while (p != head);      /* stop when we return to the start */
}
```

**Why `do-while`?** A `while (p != head)` before the first iteration would be false
immediately (since `p == head`), so the loop would never run. `do-while` always processes
the head first, then checks.

### Why use a circular list?

1. **Any node is a starting point** — you can traverse the whole ring from anywhere.
2. **No `NULL` checks** — the last node always has a valid `next`.
3. Natural fit for **round-robin** things: CPU time slicing, token ring networks,
   multiplayer turn order, music playlists on repeat.
4. Deleting the first node is cleaner: the last node just points to the new first.

**Drawbacks:** an accidental infinite loop if you forget the `p != head` condition;
slightly harder to debug; you must be careful when the list has one node (its `next`
points to itself).

---

## Insert into a circular list (sorted by exponent)

```
Algorithm: InsertSorted(head, coef, exp)
Input : Circular list head, and a term (coef, exp)
Output: List with the term inserted in descending exponent order

Step 1: Start
Step 2: if coef = 0 then Stop
Step 3: if head = NULL then
Step 4:     create node n, set n->coef, n->exp, n->next = n
Step 5:     head = n, Stop
Step 6: end if
Step 7: prev = NULL, p = head
Step 8: repeat
Step 9:     if p->exp = exp then
Step 10:        p->coef = p->coef + coef
Step 11:        if p->coef = 0 then delete p
Step 12:        Stop
Step 13:    end if
Step 14:    if p->exp < exp then exit loop
Step 15:    prev = p, p = p->next
Step 16: until p = head
Step 17: create node n with (coef, exp)
Step 18: n->next = p
Step 19: if prev = NULL then
Step 20:    find last node; last->next = n; head = n
Step 21: else
Step 22:    prev->next = n
Step 23: end if
Step 24: Stop
```

> **Note:** `prev = NULL` means "insert before the current head", which only happens when
> the new exponent is **larger than every existing one**. If the loop simply wrapped all
> the way around (`prev` = last node, `p` = head), the new exponent is the **smallest**,
> so the node must be **appended** after `prev` and the head must **not** change.

---

## Traversal and deletion

Traversal is the `do-while` above. Deleting a node `p` requires its predecessor:

```c
if (p->next == p)              /* only one node */
    head = NULL;
else
{
    if (p == head)             /* deleting the head: find the last node */
    {
        last = head;
        while (last->next != head)
            last = last->next;
        head = head->next;
        last->next = head;
    }
    else
        prev->next = p->next;
}
free(p);
```

Freeing a circular list is a variation: stop when you reach the head again.

```c
p = head->next;
while (p != head)
{
    temp = p;
    p = p->next;
    free(temp);
}
free(head);
```

Your `freeList()` in `circlell.c` does exactly this and handles the empty-list case
correctly: when `head->next == head`, `p` equals `head`, the loop body never runs, and
`head` is freed. No leak. Good.

---

# Part B — Polynomial representation

## What is a polynomial?

`3x² + 2x + 1` — a sum of **terms**. Each term is `coefficient × x^exponent`.

```
3x^2 + 2x^1 + 1x^0
```

Store each term as a node: `(coefficient, exponent)`.

```
head
 |
 v
+-----+-----+---+    +-----+-----+---+    +-----+-----+------+
|  3  |  2  | *-+--> |  2  |  1  | *-+--> |  1  |  0  | NULL |
+-----+-----+---+    +-----+-----+---+    +-----+-----+------+
 coef   exp  next     coef   exp  next     coef   exp  next
```

### Two ways to store a polynomial

| Representation | Storage | Addition |
|----------------|---------|----------|
| **Array** of size = degree+1 | `a[i]` = coefficient of `x^i` | easy, but wastes space for `x^1000 + 1` |
| **Linked list** of terms | one node per non-zero term | efficient for sparse polynomials |

**Viva answer:** *"A linked list stores only the non-zero terms, so a polynomial like
`5x¹⁰⁰⁰ + 7` needs two nodes instead of an array of 1001 elements. It also grows
dynamically."*

### Ordering convention

Terms are stored in **descending order of exponent**. This is not cosmetic — it is what
makes addition a linear merge, exactly like merging two sorted arrays. Polynomial 3:
`3x² + 2x + 1` is stored 2, 1, 0.

**Header node variant:** both `poly_add.c` and the simplified `circlell.c` use a
**dummy header node**:

```
head -> [dummy] -> [3,2] -> [2,1] -> [1,0] -> back to head
```

Benefits: the list is never truly empty (`head->next == head`), and insertion before the
first real term is the same as insertion anywhere else — no special case, no `Node **head`.

---

# Part C — Polynomial addition

## The idea (the O(m+n) merge)

Walk both **sorted descending** lists with two pointers, like merging two sorted arrays:

- `p->exp == q->exp` → add coefficients, advance both.
- `p->exp > q->exp` → copy `p`, advance `p`.
- `p->exp < q->exp` → copy `q`, advance `q`.
- one list ends → copy the rest of the other.

Ignore terms whose coefficient becomes **0**.

## Algorithm `[MEMORISE]`

```
Algorithm: PolyAdd(P1, P2)
Input : Two polynomials P1 and P2 as linked lists, sorted by descending exponent
Output: Polynomial sum = P1 + P2

Step 1: Start
Step 2: create an empty result list
Step 3: p = first term of P1, q = first term of P2
Step 4: while p != end of P1 and q != end of P2 do
Step 5:     if p->exp = q->exp then
Step 6:         c = p->coef + q->coef
Step 7:         if c != 0 then insert (c, p->exp) into result
Step 8:         p = p->next, q = q->next
Step 9:     else if p->exp > q->exp then
Step 10:        insert (p->coef, p->exp) into result
Step 11:        p = p->next
Step 12:    else
Step 13:        insert (q->coef, q->exp) into result
Step 14:        q = q->next
Step 15:    end if
Step 16: end while
Step 17: while p != end of P1 do
Step 18:    insert (p->coef, p->exp) into result, p = p->next
Step 19: end while
Step 20: while q != end of P2 do
Step 21:    insert (q->coef, q->exp) into result, q = q->next
Step 22: end while
Step 23: return result
Step 24: Stop
```

**Time: O(m + n)** where `m`, `n` are the numbers of terms. Each term is visited once.
**Space: O(m + n)** for the result.

### Trace

`P1 = 3x² + 2x + 1`
`P2 = 5x² − 2x + 7`

| p | q | Compare | Result so far |
|---|---|---------|---------------|
| (3,2) | (5,2) | equal → 3+5 = 8 | `8x²` |
| (2,1) | (−2,1) | equal → 2−2 = 0 → **skip** | `8x²` |
| (1,0) | (7,0) | equal → 1+7 = 8 | `8x² + 8` |

Final: **`8x² + 8`**. ✓

---

## Option B — the "insert each term" method

A simpler but slower way, used by both of your files:

1. Create an empty result list.
2. For every term of P1, `insert_term(result, coef, exp)`.
3. For every term of P2, `insert_term(result, coef, exp)`.

`insert_term` keeps the result sorted and combines duplicates. It is short, easy to
verify, and handles unsorted input and duplicate exponents automatically.

**Time: O(m² + n²)** in the worst case — each insertion may scan the whole growing
result. For small polynomials (exam examples) that is irrelevant, but the merge above is
the answer to *"what is the complexity of polynomial addition?"*.

If an examiner asks: *"Can you do it in O(m+n)?"* — say yes, and describe the merge.
Both answers are in your files: the merge algorithm above, and the insert-each-term
method used by `circlell.c` and `poly_add.c`.

---

# Part D — Reading your code

## `poly_add.c` — the clean, autograded version

| Lines | Function | What |
|-------|----------|------|
| 29–34 | `struct node` | `coef`, `exp`, `next` |
| 36–45 | `new_poly()` | allocate a **header node**, `head->next = head` |
| 50–86 | `insert_term()` | keep descending order, combine equal exponents, delete zero results |
| 89–102 | `read_poly()` | read `n`, then `n` pairs |
| 105–125 | `poly_add()` | new list; insert all terms of both inputs |
| 128–144 | `free_poly()` | free all nodes **and the header** |
| 147–162 | `print_poly()` | prints `%+dx^%d`, i.e. `+3x^2 -5x^0` |
| 164–178 | `main()` | read both, add, print, free |

**`insert_term` is the function to understand line by line:**

```c
prev = head;
curr = head->next;

/* 1. walk while curr's exponent is BIGGER than the new one */
while (curr != head && curr->exp > exp)
{
    prev = curr;
    curr = curr->next;
}

/* 2. same exponent? combine */
if (curr != head && curr->exp == exp)
{
    curr->coef += coef;
    if (curr->coef == 0)          /* combine to zero -> remove the node */
    {
        prev->next = curr->next;
        free(curr);
    }
}
/* 3. otherwise insert between prev and curr */
else
{
    new_node->next = curr;
    prev->next = new_node;
}
```

With a header node there is **no special case for inserting at the front**: if the new
exponent is the largest, the `while` loop does not run, `curr == head->next`, and step 3
inserts between the header and the old first node. That is the whole value of the header.

**Tested outputs** (run it yourself):

```
Input:  3  (3 2) (-5 0) (3 2)      -> coefficients 3+3 for x^2
        2  (1 2) (5 0)
P1 = +6x^2 -5x^0
P2 = +1x^2 +5x^0
SUM = +7x^2
```

The `+6` proves duplicates were combined inside **one** polynomial; the missing `x^0`
term in SUM proves `-5 + 5 = 0` was **removed**, as required.

## `circlell.c` — same header-node idea, readable output

`circlell.c` uses the same header-node insertion as `poly_add.c`. The difference is only
the input/output: it prompts for each polynomial and prints terms in a human-readable
form (`3x^2 + 2x + 5`) instead of `+3x^2 +2x^1 +5x^0`.

| Lines | Function | What |
|-------|----------|------|
| 11–26 | `newList()` | allocate the header, `head->next = head` |
| 28–65 | `insert()` | descending order, combine equal exponents, delete zero results |
| 67–80 | `create()` | read `n`, then `n` coefficient/exponent pairs |
| 82–126 | `display()` | signs, coefficient 1, exponent 0/1 special cases |
| 128–140 | `add()` | new list; insert every term of both inputs |
| 142–154 | `freeList()` | free all nodes including the header |
| 156–182 | `main()` | create both, display, add, display, free |

**Why the header makes it shorter:** with no header, inserting at the front and deleting
the first node need special cases, and `head` itself can change. With a header, every real
node has a predecessor, so the same `prev`/`cur` code works everywhere. This also removes
the old "came back to `head` after a full circle?" ambiguity entirely.

**Tested outputs:**

```
P1 = 3x^2 + 2x + 5
P2 = -3x^2 + x - 5
Sum = 3x
```

and

```
P1 = x^2 - x + 1
P2 = 0
Sum = x^2 - x + 1
```

The first test proves equal exponents combine and the constants cancel. The second proves
an empty polynomial prints `0` and the `+`/`-` signs are correct.

### `poly_add_menu.c`

This is the same algorithm with user-friendly prompts, wrapped in a macro:

```c
#ifdef INTERACTIVE
#define PROMPT(...) printf(__VA_ARGS__)
#else
#define PROMPT(...)
#endif
```

Compile with `-DINTERACTIVE` to see the prompts:

```powershell
gcc -DINTERACTIVE poly_add_menu.c -o polydemo -Wall
.\polydemo.exe
```

Without the flag, the program prints only the three result lines, so an automatic grader
can compare output exactly. This is a useful pattern to know: **separate prompts from
results** when output is graded.

---

## Polynomial multiplication (viva bonus)

For each term `(a, e1)` of P1 and each term `(b, e2)` of P2, the product contributes
`(a*b, e1+e2)`. Insert each contribution into the result with `insert_term`, which
combines equal exponents.

```
for each p in P1:
    for each q in P2:
        insert_term(result, p->coef * q->coef, p->exp + q->exp)
```

**Time:** there are `m·n` products. With `insert_term`, each insertion scans the growing
result, so the worst case is **O(m²n²)**. Collecting all products and sorting gives
**O(mn log(mn))**; an array indexed by exponent gives O(mn + m + n). This is exactly the
kind of complexity discussion that earns bonus marks.

---

## Viva — circular list and polynomials

**Q1. What is a circular linked list?**
A singly linked list in which the last node's `next` points back to the first node instead
of `NULL`, forming a ring.

**Q2. How do you traverse a circular list?**
Start at `head`, process, move to `next`, and stop when you return to `head` (using a
`do-while`).

**Q3. Why must you use `do-while`?**
Because `p == head` is true at the start; a `while` loop would not execute even once.

**Q4. How do you detect the end?**
By comparing with the head pointer, not with `NULL`.

**Q5. Advantage of a circular list?**
Any node can be a starting point, there are no `NULL` checks, and it naturally models
cyclic processes (round-robin scheduling, playlists on repeat).

**Q6. Disadvantage?**
Easy to create an infinite loop if the stopping condition is wrong; insertion and deletion
need care around the head.

**Q7. What happens with a one-node circular list?**
The node's `next` points to itself, so `head->next == head`.

**Q8. How is a polynomial represented using a linked list?**
Each node stores a coefficient, an exponent, and a pointer to the next term; terms are
kept in descending exponent order and only non-zero terms are stored.

**Q9. Why descending order?**
So that addition becomes a single linear merge of two sorted lists, O(m+n).

**Q10. Why a linked list instead of an array for a polynomial?**
It stores only non-zero terms, so `5x¹⁰⁰⁰ + 7` needs 2 nodes rather than an array of
1001; and it grows dynamically.

**Q11. What is the degree of a polynomial?**
The highest exponent with a non-zero coefficient.

**Q12. What happens when two terms have the same exponent during addition?**
Their coefficients are added. If the sum is zero, the term is removed.

**Q13. What is the time complexity of polynomial addition?**
O(m+n) with the merge algorithm; O(m²+n²) with the insert-each-term method.

**Q14. Why is a header node useful here?**
It removes the special case of inserting before the first term; `head->next == head`
cleanly means "empty", and `head` never changes.

**Q15. How do you add a term with an exponent that is already present?**
Add the coefficients; if the result is 0, delete the node.

**Q16. How would you evaluate a polynomial for a given x?**
Traverse the terms and accumulate `sum += coef * pow(x, exp)`. For efficiency use
Horner's rule on an array representation.

**Q17. Can you represent a polynomial with two arrays?**
Yes: one array of coefficients and one of exponents, with a count. Addition is a merge of
the two sorted arrays.

**Q18. What is a sparse polynomial?**
One with few non-zero terms relative to its degree — the case where a linked list wins.

**Q19. How do you free a circular list?**
Save `head->next`, loop freeing nodes until you return to `head`, then free `head`.

**Q20. Difference between circular and doubly linked list?**
Circular: one link per node, last points to first. Doubly: two links per node
(`prev` and `next`), can traverse both ways; can also be made circular.

---

## Traps checklist

- [ ] Empty circular list is `head == NULL` (no header) or `head->next == head` (header).
- [ ] Traverse with `do-while (p != head)`.
- [ ] Insert in descending exponent order; combine equal exponents; drop zero terms.
- [ ] `p == head` after a full loop is **not** the same as "insert at front" — use `prev`.
- [ ] In `add`, handle "one list exhausted" separately (copy the rest).
- [ ] Free every node, including the header node.
- [ ] When printing, handle the empty polynomial (`0`).
- [ ] Say out loud that the optimal algorithm is O(m+n).

---

**Next:** `10_VIVA_EXPRESS.md`
