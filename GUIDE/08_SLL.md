# 08 — Singly Linked List (Workshop Enrollment System)

**File:** `singlyll.c`
**Exam value:** very high. "Write a program to implement a singly linked list with
insert, delete, display and reverse" is one of the most common practical questions.

---

## 1. Why a linked list?

An array is a fixed block of memory. Inserting in the middle requires **shifting** every
later element. A linked list stores each element in its own block (a **node**) and links
them with pointers, so inserting just means **changing two pointers**.

```
ARRAY:        [10][20][30][40][50]        contiguous, fixed size

LINKED LIST:  head
               |
               v
            +----+---+    +----+---+    +----+---+    +----+------+
            | 10 | *-+--> | 20 | *-+--> | 30 | *-+--> | 40 | NULL |
            +----+---+    +----+---+    +----+---+    +----+------+
              data next     data next     data next     data next
```

The last node's `next` is `NULL`, meaning "end of list".

### Array vs linked list

| | Array | Singly Linked List |
|---|---|---|
| Size | fixed at compile time | grows/shrinks at runtime |
| Memory | contiguous | scattered, plus a pointer per node |
| Access by index | **O(1)** | **O(n)** (must walk) |
| Insert/delete at front | O(n) (shift) | **O(1)** |
| Insert/delete in middle | O(n) (shift) | O(n) to find + O(1) to relink |
| Wasted memory | possible (unused slots) | none, but pointers cost extra |
| Reverse traversal | easy | hard (needs recursion or a second pass) |
| Binary search | possible | not practical |
| Cache performance | good | poor |

**One-line viva answer:** *"Arrays are better for random access; linked lists are better
when the number of elements changes often and insertions/deletions dominate."*

---

## 2. The node

```c
struct Student
{
    int regNo;
    char name[50];
    struct Student *next;    /* pointer to the next node */
};
```

This is a **self-referential structure**: a struct containing a pointer to its own type.

```
+-------------------+
| regNo   : int     |
| name    : char[50]|
| next    : *Node --+----> next node (or NULL)
+-------------------+
```

`head` is just a pointer to the first node. It is the **only way** to reach the list.

```c
struct Student *head = NULL;    /* NULL = empty list */
```

In your file `head` is a **global** variable (line 13), which is why the functions do not
need to return it. If it were local to `main`, every insert/delete would need
`struct Student **head` or a return value.

---

## 3. The five operations, drawn

### A. Create a node

```c
newNode = (struct Student *) malloc(sizeof(struct Student));
newNode->regNo = 101;
strcpy(newNode->name, "Aarav");
newNode->next = NULL;
```

Always: **allocate → fill → set `next`**. Three steps, every time.

### B. Insert at the beginning — O(1)

```
Before:  head -> [A] -> [B] -> NULL
After:   head -> [N] -> [A] -> [B] -> NULL
```

```c
newNode->next = head;    /* 1. new node points to old first */
head = newNode;          /* 2. head points to new node     */
```

**Order matters.** If you do `head = newNode` first, you lose the rest of the list.

### C. Insert at the end — O(n)

Walk to the last node, then attach:

```
Before:  head -> [A] -> [B] -> NULL
After:   head -> [A] -> [B] -> [N] -> NULL
```

```c
newNode->next = NULL;

if (head == NULL)
    head = newNode;                 /* special case: empty list */
else
{
    temp = head;
    while (temp->next != NULL)      /* stop AT the last node */
        temp = temp->next;

    temp->next = newNode;           /* attach      */
}
```

**Why `temp->next != NULL` and not `temp != NULL`?** Because we need to stop at the
**last** node so we can modify its `next`. If the loop were `temp != NULL`, `temp` would
become `NULL` and we would have nothing to attach to.

This is exactly what `addStudent()` in your file does (lines 32–40).

### D. Delete a node — three cases

```
Before:  head -> [A] -> [B] -> [C] -> NULL        delete B
After:   head -> [A] ---------> [C] -> NULL
```

You must keep track of the node **before** the one you delete, because you have to
redirect its `next`.

```c
temp = head;
prev = NULL;

while (temp != NULL && temp->regNo != reg)   /* find the node */
{
    prev = temp;
    temp = temp->next;
}

if (temp == NULL)          /* case 1: not found */
    printf("Not found\n");
else
{
    if (prev == NULL)      /* case 2: deleting the first node */
        head = temp->next;
    else                   /* case 3: deleting a middle/last node */
        prev->next = temp->next;

    free(temp);            /* give memory back */
}
```

**Three cases to always mention:** empty/not found, first node (must move `head`),
middle or last node (must change `prev->next`).

This is `removeStudent()` in your file, lines 45–72 — including the `prev == NULL`
special case on line 65.

### E. Reverse — the classic interview/exam question

You cannot go backwards, so you must reverse the arrows as you walk forward, keeping
three pointers: `prev`, `current`, `next`.

```
Initial:   NULL     [1] -> [2] -> [3] -> NULL
                    ^prev  ^curr

Step 1:    NULL <- [1]     [2] -> [3] -> NULL
                    ^prev   ^curr
Step 2:    NULL <- [1] <- [2]     [3] -> NULL
                            ^prev  ^curr
Step 3:    NULL <- [1] <- [2] <- [3]     NULL
                                   ^prev  ^curr = NULL

head = prev  ->  [3] -> [2] -> [1] -> NULL
```

```c
prev = NULL;
current = head;

while (current != NULL)
{
    next = current->next;     /* 1. SAVE the rest of the list  */
    current->next = prev;     /* 2. reverse this arrow         */
    prev = current;           /* 3. advance prev               */
    current = next;           /* 4. advance current            */
}

head = prev;
```

**The order is everything.** `next = current->next` must happen first; after
`current->next = prev`, the original next node is unreachable unless you saved it.

This is `reverseList()` in your file, lines 132–146. Memorise those five lines.

### F. Traverse / display

```c
temp = head;
while (temp != NULL)
{
    printf("%d\t%s\n", temp->regNo, temp->name);
    temp = temp->next;          /* DO NOT FORGET THIS */
}
```

Forgetting `temp = temp->next` gives an **infinite loop** that prints the first node
forever. It is the single most common linked-list bug.

---

## 4. Exam-ready algorithms

### Insert at end `[MEMORISE]`

```
Algorithm: InsertAtEnd(head, value)
Input : Head pointer of the list and the value to insert
Output: List with the new node at the end

Step 1: Start
Step 2: newNode = allocate memory for a node
Step 3: newNode->data = value
Step 4: newNode->next = NULL
Step 5: if head = NULL then
Step 6:     head = newNode
Step 7: else
Step 8:     temp = head
Step 9:     while temp->next != NULL do
Step 10:        temp = temp->next
Step 11:    end while
Step 12:    temp->next = newNode
Step 13: end if
Step 14: Stop
```

### Delete a node by value `[MEMORISE]`

```
Algorithm: DeleteNode(head, key)
Input : Head pointer and the value to delete
Output: List without the node, or unchanged if not found

Step 1: Start
Step 2: temp = head, prev = NULL
Step 3: while temp != NULL and temp->data != key do
Step 4:     prev = temp
Step 5:     temp = temp->next
Step 6: end while
Step 7: if temp = NULL then
Step 8:     print "Node not found"
Step 9:     Stop
Step 10: end if
Step 11: if prev = NULL then
Step 12:    head = temp->next
Step 13: else
Step 14:    prev->next = temp->next
Step 15: end if
Step 16: free(temp)
Step 17: Stop
```

### Reverse a list `[MEMORISE]`

```
Algorithm: ReverseList(head)
Input : Head pointer of the singly linked list
Output: Head pointer of the reversed list

Step 1: Start
Step 2: prev = NULL, current = head
Step 3: while current != NULL do
Step 4:     next = current->next
Step 5:     current->next = prev
Step 6:     prev = current
Step 7:     current = next
Step 8: end while
Step 9: head = prev
Step 10: return head
Step 11: Stop
```

### Count nodes

```
Algorithm: CountNodes(head)
Step 1: Start
Step 2: count = 0, temp = head
Step 3: while temp != NULL do
Step 4:     count = count + 1
Step 5:     temp = temp->next
Step 6: end while
Step 7: return count
Step 8: Stop
```

### Search

```
Algorithm: Search(head, key)
Step 1: Start
Step 2: pos = 1, temp = head
Step 3: while temp != NULL do
Step 4:     if temp->data = key then return pos
Step 5:     pos = pos + 1, temp = temp->next
Step 6: end while
Step 7: return -1
Step 8: Stop
```

Complexity: O(n). Note that **searching a linked list cannot be O(log n)** even if
sorted, because there is no random access to the middle.

---

## 5. What each function in `singlyll.c` does

| Lines | Function | Logic |
|-------|----------|-------|
| 6–11 | `struct Student` | node: regNo, name, next |
| 13 | `head = NULL` | global head, empty list |
| 15–43 | `addStudent()` | malloc → check → read → append at end |
| 45–72 | `removeStudent()` | search by regNo → unlink → free |
| 74–90 | `display()` | traverse with `temp != NULL` |
| 92–104 | `countStudents()` | traverse, count |
| 106–130 | `sortStudents()` | bubble sort **swapping data**, not nodes |
| 132–146 | `reverseList()` | three-pointer reversal |
| 148–201 | `main()` | menu, then free all nodes before exit |

### Two design choices worth defending in viva

1. **Sorting by swapping `regNo` and `name` instead of relinking nodes.**
   Simpler and safe (no pointer juggling). It is O(n²) data copies but O(1) extra
   memory. Relinking would be faster for large records but much easier to get wrong.
   Say: *"I swap the data fields, which keeps the list structure untouched."*

2. **Freeing the whole list at exit** (lines 193–198). Good practice; mention it as
   avoiding a memory leak.

### Dry run: reverse `10 → 20 → 30`

| Iteration | prev | current | next | List after `current->next = prev` |
|-----------|------|---------|------|-----------------------------------|
| start | NULL | 10 | — | 10 → 20 → 30 |
| 1 | NULL | 10 | 20 | NULL ← 10, then prev=10, current=20 |
| 2 | 10 | 20 | 30 | 10 ← 20, then prev=20, current=30 |
| 3 | 20 | 30 | NULL | 20 ← 30, then prev=30, current=NULL |
| end | 30 | NULL | — | head = 30 → **30 → 20 → 10** |

### Dry run: delete `20` from `10 → 20 → 30`

| Step | temp | prev | Condition |
|------|------|------|-----------|
| start | 10 | NULL | 10 ≠ 20 → continue |
| after loop body | 20 | 10 | 20 = 20 → stop |
| unlink | — | 10 | `prev->next = temp->next` → 10 points to 30 |
| free | — | — | **10 → 30** |

---

## 6. The dummy header node variant (know it for viva)

Your earlier template (in git history, `sll_workshop.c`) used a **dummy header node**:

```
head -> [header] -> [student 1] -> [student 2] -> ... -> NULL
```

- The header holds no data; it exists only to simplify the code.
- `head` **never changes**, so no function needs `Node **head` or a return value.
- Empty list is `head->next == NULL`.
- Inserting at the front is the same as inserting after the header — no special case.
- Deleting the first real node is the same as deleting any other node — no special case.

**Viva:** *"What is a dummy/header node?"* → A node with no data placed before the first
real node, used to remove the special cases for an empty list and for operations at the
front.

Most textbook exams use the **no-header** version, which is what your `singlyll.c`
implements. Be ready to explain both, and be able to say which one you used.

---

## 7. Why `Node **head`?

If a function must **change `head` itself** (insert at front, delete the first node),
passing `Node *head` is not enough: C passes the pointer by value, so the function gets
a copy. Changing the copy does not change `main`'s variable.

```c
void insertFront(struct Student **head, int reg)
{
    struct Student *n = malloc(sizeof(struct Student));
    n->regNo = reg;
    n->next = *head;      /* dereference to get the real head */
    *head = n;            /* update the caller's head          */
}
```

Your code sidesteps this by making `head` **global**. That is acceptable in an exam
program but worth explaining: *"I used a global head so all functions share it; the
alternative is to pass `Node **head`."*

**Rule of thumb:**
- Only reading/traversing → `Node *head` is fine.
- Modifying the first node → need `Node **head` (or a header node, or a global).

---

## 8. Viva — singly linked list

**Q1. What is a linked list?**
A linear collection of nodes, each containing data and a pointer to the next node, stored
in non-contiguous memory and accessed through a head pointer.

**Q2. What is a node?**
The basic unit: a structure with a data field (or fields) and a `next` pointer.

**Q3. What is `head`?**
A pointer to the first node. If `head == NULL`, the list is empty.

**Q4. What does the last node's `next` contain?**
`NULL`, marking the end.

**Q5. Why is the struct self-referential?**
Because each node must point to another node of the same type.

**Q6. Array vs linked list?**
Array: O(1) random access, fixed size, shifting on insert/delete. Linked list: O(n)
access, dynamic size, O(1) insert/delete once the position is known.

**Q7. Time complexity of inserting at the beginning?**
O(1).

**Q8. Time complexity of inserting at the end?**
O(n) without a tail pointer, O(1) with one.

**Q9. How can you delete a node given only a pointer to it?**
Copy the next node's data into it, then delete the next node — O(1). This fails if the
node is the last one, because there is no next node to copy from.

**Q10. Why is searching O(n)?**
There is no indexing; you must follow `next` pointers from the head.

**Q11. Can you binary search a linked list?**
Not practically — binary search needs O(1) access to the middle.

**Q12. How do you reverse a singly linked list?**
Iteratively with three pointers (`prev`, `current`, `next`), reversing each `next`
pointer in one pass. O(n) time, O(1) space.

**Q13. How do you find the middle element in one pass?**
Floyd's slow/fast pointer: `slow = slow->next`, `fast = fast->next->next`. When `fast`
reaches the end, `slow` is at the middle.

**Q14. How do you detect a loop (cycle)?**
Floyd's cycle detection: if slow and fast ever meet, there is a cycle.

**Q15. How do you find the length of a loop?**
Once slow and fast meet, keep one pointer fixed and move the other around the loop,
counting until it returns.

**Q16. What is a memory leak in a linked list?**
Deleting a node from the list without calling `free`, or losing the head pointer so the
whole list becomes unreachable.

**Q17. Why must you save `current->next` before reversing?**
Because `current->next = prev` overwrites the only link to the rest of the list.

**Q18. What is a dummy header node and why use it?**
A data-less node before the first element that removes special cases for empty lists and
front operations. `head` then never changes.

**Q19. Difference between `Node *head` and `Node **head`?**
`Node *head` passes a copy of the pointer (read-only in effect). `Node **head` passes
the address of the pointer, allowing the function to change which node is first.

**Q20. Can a linked list be sorted?**
Yes — bubble/insertion by swapping data, or merge sort by relinking. Merge sort is the
standard O(n log n) choice for linked lists.

**Q21. What happens if you `free(temp)` and then use `temp->next`?**
Undefined behaviour — you are reading freed memory (a dangling pointer). Save `next`
first.

**Q22. How do you merge two sorted linked lists?**
Merge like merge sort: repeatedly take the smaller head of the two lists and append it to
the result. O(m+n).

**Q23. How do you delete the entire list?**
While `head != NULL`: save `head->next`, `free(head)`, `head = next`.

**Q24. Where are linked-list nodes stored?**
On the **heap**, allocated by `malloc`; only the head pointer is a local/global variable.

---

## 9. Traps checklist

- [ ] After `malloc`, check for `NULL`.
- [ ] Set `newNode->next = NULL` explicitly.
- [ ] Insert at end: stop at `temp->next == NULL`, not `temp == NULL`.
- [ ] Delete: handle first node separately (`prev == NULL`).
- [ ] Delete: `free` the node and do not touch it afterwards.
- [ ] Traverse: never forget `temp = temp->next`.
- [ ] Reverse: save `next` **before** changing `current->next`.
- [ ] Print a message when the list is empty.
- [ ] In the algorithm, explicitly mention the empty-list case.
- [ ] State the complexity of each operation.

---

**Next:** `09_CLL_POLY.md`
