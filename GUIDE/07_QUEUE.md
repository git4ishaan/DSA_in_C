# 07 — Queue: Linear and Circular

**Files:** `linear_queue.c`, `circular_queue.c`
**Exam value:** high. The standard question is *"implement a queue using an array and
explain the drawback of a linear queue"* — the circular queue is the answer to the
drawback.

---

## 1. What is a queue?

A **FIFO** (First In, First Out) structure. Elements join at the **rear** and leave from
the **front**, like a line at a ticket counter.

```
   dequeue (leave)                              enqueue (join)
        <--  +-----+-----+-----+-----+-----+  <--
             | 10  | 20  | 30  | 40  | 50  |
             +-----+-----+-----+-----+-----+
              front                     rear
```

**Terms:**

- `front` — index of the element that will leave next.
- `rear` — index of the most recently inserted element.

**Operations (all O(1)):**

| Operation | Meaning |
|-----------|---------|
| `enqueue(x)` | insert `x` at the rear |
| `dequeue()` | remove and return the element at the front |
| `peek()` | look at the front without removing |
| `isEmpty()` | no elements |
| `isFull()` | no space |

**Applications:** printer spooling (your `linear_queue.c` is literally a print queue),
CPU round-robin scheduling, keyboard buffers, BFS traversal, call-centre waiting lines,
I/O buffering, message queues.

---

# Part A — Linear queue

## The idea

`enqueue` puts the item at `rear + 1`. `dequeue` takes the item at `front` and moves
`front` forward. Nothing ever moves backwards, so **space at the beginning is never
reused**.

## State rules (memorise)

```
Initially:  front = -1, rear = -1

isEmpty:    front == -1            (or front > rear)
isFull:     rear == MAX - 1
enqueue:    if front == -1 then front = 0
            rear = rear + 1
            queue[rear] = x
dequeue:    x = queue[front]
            front = front + 1
```

## Algorithm `[MEMORISE]`

```
Algorithm: Enqueue(Q, MAX, front, rear, x)
Step 1: Start
Step 2: if rear = MAX-1 then
Step 3:     print "Queue Overflow"
Step 4:     Stop
Step 5: end if
Step 6: if front = -1 then
Step 7:     front = 0
Step 8: end if
Step 9: rear = rear + 1
Step 10: Q[rear] = x
Step 11: Stop
```

```
Algorithm: Dequeue(Q, front, rear)
Step 1: Start
Step 2: if front = -1 or front > rear then
Step 3:     print "Queue Underflow"
Step 4:     Stop
Step 5: end if
Step 6: x = Q[front]
Step 7: front = front + 1
Step 8: if front > rear then
Step 9:     front = -1, rear = -1        // queue became empty, reset
Step 10: end if
Step 11: return x
Step 12: Stop
```

**Time:** O(1) for both. **Space:** O(MAX).

## The drawback: false overflow

`MAX = 5`. Enqueue 10, 20, 30, 40, 50 → `rear = 4`, queue is full.

```
 index:   0     1     2     3     4
        +-----+-----+-----+-----+-----+
        | 10  | 20  | 30  | 40  | 50  |
        +-----+-----+-----+-----+-----+
         front                     rear
```

Dequeue twice → `front = 2`, `rear = 4`. Two slots (0 and 1) are empty:

```
 index:   0     1     2     3     4
        +-----+-----+-----+-----+-----+
        | --  | --  | 30  | 40  | 50  |
        +-----+-----+-----+-----+-----+
                     front       rear
```

Now `enqueue(60)` → the check `rear == MAX-1` is **true** → **"Queue Overflow"**.

But there **is** free space at indices 0 and 1! The queue only *appears* full because
`rear` hit the end of the array. This is called **false overflow** (or "drifting queue").

```
        +-----+-----+-----+-----+-----+
        |     |     | 30  | 40  | 50  |   rear = 4 = MAX-1  -> says FULL
        +-----+-----+-----+-----+-----+
         free  free  front
```

Also called the **"moving queue"** problem: the whole queue slowly walks off the right
edge of the array.

### Ways to fix it

1. **Shift everything left** after each dequeue — O(n) per dequeue, wasteful.
2. **Reset** `front = rear = -1` when the queue empties — helps only if it *fully*
   empties. Your `linear_queue.c` does this (lines 56–61), which is why it works fine
   for simple demo runs, but it does not fix the partial case above.
3. **Circular queue** — wrap `rear` back to 0 using modulo. Elegant, O(1). ← the right
   answer.

## How `linear_queue.c` is built

| Lines | What |
|-------|------|
| 6–10 | `struct Job { int id; char title[50]; }` — the queue stores **records**, not ints |
| 12–13 | `queue[MAX]`, `front = rear = -1` |
| 16–39 | `enqueue`: overflow check, read job, set `front` if first, `rear++`, copy |
| 42–62 | `dequeue`: underflow check, print the job, `front++`, reset if now empty |
| 65–82 | `display`: `for (i = front; i <= rear; i++)` — only the live range |
| 85–124 | menu loop |

**Records in a queue:** note `queue[rear] = job;` copies the whole struct in one
assignment. That works in C because structs are assignable. In an exam this is a nice
touch: *"A queue of structs stores complete records, so the ID and title stay together."*

---

# Part B — Circular queue

## The idea

Treat the array as a **circle**: after index `MAX-1` comes index 0.

```
               0
         4  /     \  1
           |       |
         3  \     /  2
               
   rear = (rear + 1) % MAX
   front = (front + 1) % MAX
```

`% MAX` (modulo) is the whole trick: `4 + 1 = 5`, and `5 % 5 = 0`, so it wraps.

## State rules (memorise)

```
Initially:  front = -1, rear = -1

isEmpty:    front == -1
isFull:     (rear + 1) % MAX == front
enqueue:    if front == -1 then front = 0, rear = 0
            else rear = (rear + 1) % MAX
dequeue:    if front == rear then front = -1, rear = -1   (last element removed)
            else front = (front + 1) % MAX
```

**Very important detail about capacity.** There are two common initialisations:

| Variant | Initial | Empty test | Full test | Capacity |
|---------|---------|-----------|-----------|----------|
| **Yours** | `front = rear = -1` | `front == -1` | `(rear+1)%MAX == front` | **MAX** |
| Textbook | `front = rear = 0` | `front == rear` | `(rear+1)%MAX == front` | **MAX − 1** |

The textbook variant "sacrifices one slot" because index 0 doubles as the initial
empty marker. **Your code uses the `-1` sentinel, so it can hold all `MAX` items.**
If a viva examiner says "a circular queue wastes one slot", explain this distinction —
it shows you understand *why* the condition exists rather than reciting it.

## Algorithm `[MEMORISE]`

```
Algorithm: CircularEnqueue(Q, MAX, front, rear, x)
Step 1: Start
Step 2: if (rear + 1) % MAX = front then
Step 3:     print "Queue Overflow"
Step 4:     Stop
Step 5: end if
Step 6: if front = -1 then
Step 7:     front = 0, rear = 0
Step 8: else
Step 9:     rear = (rear + 1) % MAX
Step 10: end if
Step 11: Q[rear] = x
Step 12: Stop
```

```
Algorithm: CircularDequeue(Q, MAX, front, rear)
Step 1: Start
Step 2: if front = -1 then
Step 3:     print "Queue Underflow"
Step 4:     Stop
Step 5: end if
Step 6: x = Q[front]
Step 7: if front = rear then
Step 8:     front = -1, rear = -1
Step 9: else
Step 10:    front = (front + 1) % MAX
Step 11: end if
Step 12: return x
Step 13: Stop
```

## Dry run — watch it wrap (MAX = 5)

Start: `front = -1, rear = -1`

| Operation | front | rear | Array (index 0..4) | Comment |
|-----------|-------|------|--------------------|---------|
| enqueue 10 | 0 | 0 | 10, —, —, —, — | first item |
| enqueue 20 | 0 | 1 | 10, 20, —, —, — | |
| enqueue 30 | 0 | 2 | 10, 20, 30, —, — | |
| enqueue 40 | 0 | 3 | 10, 20, 30, 40, — | |
| dequeue → 10 | 1 | 3 | 10, 20, 30, 40, — | front moves |
| dequeue → 20 | 2 | 3 | 10, 20, 30, 40, — | slots 0,1 dead |
| enqueue 50 | 2 | 4 | 10, 20, 30, 40, 50 | |
| enqueue 60 | 2 | **0** | 60, 20, 30, 40, 50 | **wrapped!** slot 0 reused |
| enqueue 70 | 2 | **1** | 60, 70, 30, 40, 50 | slot 1 reused |

Now `(rear+1)%5 = 2 = front` → **full**.

**Logical order of the queue** is not the array order. Read starting at `front` and wrap:

```
front = 2  ->  30, 40, 50, 60, 70        (5 items)
```

That is exactly why `display()` starts at `front` and stops at `rear`:

```c
i = front;
while (1)
{
    printf(... queue[i] ...);
    if (i == rear) break;          /* stop AFTER printing rear */
    i = (i + 1) % MAX;             /* wrap */
}
```

**Get the display loop right in the exam.** The `break` must come **after** printing and
**before** incrementing, otherwise you either skip the last element or loop forever.

## How `circular_queue.c` is built

| Lines | What |
|-------|------|
| 15–39 | `enqueue`: full check, first-item special case, `rear = (rear+1)%MAX` |
| 42–58 | `dequeue`: empty check, last-item special case, `front = (front+1)%MAX` |
| 61–82 | `display`: wrap-around traversal |
| 85–122 | menu |

## The `front == rear` special case

When the queue has exactly **one** element, `front == rear`. After removing it the queue
is empty, and setting `front = (front+1)%MAX` alone would leave `front == rear` pointing
at a slot — indistinguishable from "one element". That is why both are reset to `-1`.
This case is worth a mark in a written answer.

---

## Linear vs circular — the comparison table for your answer

| | Linear Queue | Circular Queue |
|---|---|---|
| Rear movement | `rear++` | `rear = (rear+1) % MAX` |
| Reuses freed space | No | Yes |
| False overflow | **Yes** | No |
| Full condition | `rear == MAX-1` | `(rear+1) % MAX == front` |
| Empty condition | `front == -1` | `front == -1` |
| Time per operation | O(1) | O(1) |
| Extra cost | none | one modulo operation |

---

## Viva — queue

**Q1. Define a queue.**
A linear data structure that follows FIFO: insertion at the rear, deletion at the front.

**Q2. What are `front` and `rear`?**
`front` is the index of the next element to be deleted; `rear` is the index of the last
inserted element.

**Q3. Queue overflow and underflow?**
Overflow = enqueue when full. Underflow = dequeue when empty.

**Q4. Give the postfix equivalent of... (no) — what is the main drawback of a linear queue?**
False overflow: after some dequeues, free slots at the beginning cannot be reused, so
the queue reports full even though space exists.

**Q5. How does a circular queue solve it?**
By incrementing `front` and `rear` modulo `MAX`, so indices wrap around and freed slots
are reused.

**Q6. Why is modulo used?**
`(rear + 1) % MAX` maps the index after the last slot back to 0, turning the array into
a circle.

**Q7. How is a full circular queue detected?**
`(rear + 1) % MAX == front`. This distinguishes full from empty, because in the empty
state `front == -1` (or `front == rear` in the other convention).

**Q8. Why is one slot sometimes wasted?**
In the `front = rear = 0` convention, `front == rear` must mean empty, so one slot is
reserved to keep "full" distinguishable. With the `-1` sentinel, all `MAX` slots are usable.

**Q9. How can you use all slots without wasting one?**
Keep a separate `count` variable: full when `count == MAX`, empty when `count == 0`.

**Q10. Difference between stack and queue?**
Stack = LIFO, one end. Queue = FIFO, two ends.

**Q11. Can a queue be implemented using two stacks?**
Yes. Enqueue pushes onto stack S1. Dequeue pops from S2; if S2 is empty, move all of S1
into S2 first (which reverses the order), then pop. Amortised O(1).

**Q12. What is a priority queue?**
A queue where each element has a priority and the highest-priority element leaves first,
regardless of arrival order. Usually implemented with a heap. Used in OS scheduling and
Dijkstra's algorithm.

**Q13. What is a deque?**
Double-ended queue — insertion and deletion allowed at both ends.

**Q14. Give real applications of queues.**
Printer spooling, CPU round-robin scheduling, keyboard/IO buffers, BFS, call centres,
message and task queues.

**Q15. Complexity of enqueue and dequeue?**
O(1) for both array and linked-list implementations.

**Q16. How would you implement a queue with a linked list?**
Keep `front` and `rear` pointers. Enqueue = insert at the tail (O(1) with a rear
pointer). Dequeue = delete the head (O(1)). No overflow until memory runs out.

**Q17. Which is better, array or linked-list queue?**
Array: simple, cache-friendly, fixed size. Linked list: dynamic size, no false overflow,
extra pointer memory.

---

## Traps checklist

- [ ] `front = rear = -1` initially.
- [ ] On the first enqueue, set `front = 0` as well as `rear = 0`.
- [ ] Overflow check **before** inserting; underflow check **before** removing.
- [ ] Circular: `% MAX` on **both** increments.
- [ ] Circular display: start at `front`, stop after printing `rear`, wrap in between.
- [ ] Reset both `front` and `rear` when the last element is removed.
- [ ] In the algorithm, write the modulo expression exactly — it is the key step and
      examiners look for it.

---

**Next:** `08_SLL.md`
