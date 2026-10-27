# 10 — Viva Express: 120 Questions, One-Line Answers

Read one section per day. Cover the right column, answer aloud, then check.
If you can answer 80% of these, the viva is won.

---

## A. C fundamentals (1–22)

1. **What is a pointer?** A variable that stores the memory address of another variable.
2. **What does `*` mean?** In a declaration, "pointer to"; in an expression, "value at this address" (dereference).
3. **What does `&` mean?** "Address of".
4. **What is `NULL`?** A special pointer constant meaning "points to nothing"; usually `(void *)0`.
5. **Why initialise a pointer to `NULL`?** So you can test it before dereferencing and avoid a wild pointer.
6. **What is a dangling pointer?** A pointer to memory that has been freed or gone out of scope.
7. **What is a memory leak?** Allocating memory with `malloc` and never calling `free`, so it stays reserved.
8. **`malloc` vs `calloc`?** `malloc(n)` allocates `n` bytes uninitialised; `calloc(k,n)` allocates `k×n` bytes and zero-fills them.
9. **What does `free` do?** Returns heap memory to the system; it does not change the pointer, so set it to `NULL` afterwards.
10. **Where does `malloc` get memory?** From the heap. Local variables live on the stack.
11. **What is a structure?** A user-defined type grouping variables of different types under one name.
12. **`. ` vs `->`?** `.` accesses a member of a struct variable; `->` accesses a member through a pointer to a struct.
13. **What is a self-referential structure?** A struct containing a pointer to its own type — the basis of linked lists and trees.
14. **What is `typedef`?** It creates a new name (alias) for an existing type, e.g. `typedef struct node Node;`.
15. **What is the difference between an array and a pointer?** An array name is a constant address of a contiguous block; a pointer is a variable that can be reassigned.
16. **What is row-major order?** Storing a 2D array row by row: all of row 0, then row 1, etc.
17. **Array index range for `int a[10]`?** `0` to `9`.
18. **Does C check array bounds?** No. Out-of-bounds access is undefined behaviour.
19. **Why does `scanf` need `&` for an `int`?** To pass the address so `scanf` can store the value there.
20. **Why is `'\0'` important?** It marks the end of a string; all `str*` functions rely on it.
21. **`strcmp` return values?** 0 if equal, negative if first is smaller, positive if first is larger.
22. **How are arguments passed in C?** By value — the function receives copies; pass addresses to modify the caller's variables.

---

## B. Complexity (23–32)

23. **What is time complexity?** How the running time grows with input size, expressed in big-O.
24. **O(1) means?** Constant time, independent of input size.
25. **O(n)?** Linear — time grows proportionally to input size.
26. **O(log n)?** Each step halves the problem (binary search).
27. **O(n log n)?** Typical of efficient comparison sorts (merge, heap, quicksort average).
28. **O(n²)?** Quadratic — typical of nested loops (bubble, selection, insertion sort).
29. **Best, average, worst case?** Minimum, typical, and maximum time over all inputs of size `n`.
30. **What is space complexity?** Extra memory used as a function of input size, excluding the input itself.
31. **What is an in-place algorithm?** One using O(1) extra space.
32. **Why do we care about complexity?** To predict performance and choose the right algorithm for the input size.

---

## C. Arrays and matrices (33–42)

33. **What is a matrix?** A 2D array accessed as `A[i][j]` with `i` = row, `j` = column.
34. **Condition for matrix addition?** Same order `m × n`.
35. **Condition for matrix multiplication?** Columns of A = rows of B; `A[m][n] × B[n][p] → C[m][p]`.
36. **Complexity of matrix multiplication?** O(m·n·p), i.e. O(n³) for square matrices.
37. **What is transpose?** Interchanging rows and columns: `T[j][i] = A[i][j]`.
38. **In-place transpose of a square matrix?** Swap `A[i][j]` with `A[j][i]` for `j > i` only.
39. **What is a symmetric matrix?** A square matrix equal to its transpose.
40. **What is an identity matrix?** A square matrix with 1s on the main diagonal, 0 elsewhere.
41. **What is a saddle point?** An element that is the minimum of its row and the maximum of its column.
42. **Can a matrix have multiple saddle points?** Yes, or none.

---

## D. Searching and sorting (43–60)

43. **What is searching?** Locating the position of a key in a collection.
44. **Linear search complexity?** O(n) worst/average, O(1) best.
45. **Binary search complexity?** O(log n), best O(1).
46. **Precondition for binary search?** The array must be sorted.
47. **Why `low <= high`?** When `low == high` there is still one element to check.
48. **Why `mid + 1` / `mid - 1`?** `mid` itself has been checked, so exclude it or you may loop forever.
49. **Can binary search be used on a linked list?** No, because it needs O(1) access to the middle.
50. **Which search for unsorted data searched once?** Linear search.
51. **What is sorting?** Arranging elements in a defined order by some key.
52. **Bubble sort idea?** Repeatedly swap adjacent out-of-order pairs; after each pass the largest is in place.
53. **Selection sort idea?** Repeatedly select the smallest remaining element and swap it into position.
54. **Insertion sort idea?** Insert each element into its correct place in the already-sorted prefix.
55. **Shell sort idea?** Insertion sort with a shrinking gap so elements move long distances early.
56. **Which sorts are stable?** Bubble and insertion. Selection and shell are not.
57. **What is a stable sort?** Equal elements keep their original relative order.
58. **Which sort does the fewest swaps?** Selection sort, at most `n−1`.
59. **Which is best for nearly sorted data?** Insertion sort, O(n).
60. **Best case of bubble sort?** O(n) with the early-exit `swapped` flag; O(n²) without it.

---

## E. Sparse matrices (61–70)

61. **What is a sparse matrix?** A matrix in which most elements are zero (typically more than two-thirds).
62. **Why special storage?** To save memory and skip useless operations on zeros.
63. **What is a triplet?** A `(row, column, value)` record for one non-zero element.
64. **What is in the header row?** Total rows, total columns, and number of non-zero elements.
65. **How is the triplet array ordered?** By row, then by column (row-major).
66. **Memory for triplets?** `3(t+1)` integers for `t` non-zeros.
67. **Simple transpose complexity?** O(columns × t).
68. **Fast transpose complexity?** O(columns + t).
69. **Steps of fast transpose?** Count non-zeros per column → prefix-sum into start positions → place each triplet in one pass.
70. **Condition for adding two sparse matrices?** Same number of rows and columns.

---

## F. Stack (71–85)

71. **What is a stack?** A LIFO structure with insertion and deletion at one end (the top).
72. **Primary operations?** `push` and `pop`, both O(1).
73. **Stack overflow?** Push when `top == MAX−1`.
74. **Stack underflow?** Pop when `top == −1`.
75. **Why `top = −1` initially?** So the first push makes it 0; −1 means empty.
76. **What is infix?** Operator between operands: `A+B`.
77. **What is postfix?** Operator after operands: `AB+`.
78. **What is prefix?** Operator before operands: `+AB`.
79. **Why do compilers prefer postfix?** No parentheses or precedence rules; a single stack pass evaluates it.
80. **Postfix of `A+B*C`?** `A B C * +`.
81. **Postfix of `(A+B)*C`?** `A B + C *`.
82. **Which stack for infix→postfix?** A stack of characters (operators).
83. **In postfix evaluation, which operand is popped first?** The right operand (the top), then the left.
84. **Evaluate `5 3 2 * +`?** `11` (3×2 = 6, 5+6 = 11).
85. **Where is the stack used in recursion?** The system call stack stores each call's parameters, locals and return address.

---

## G. Queue (86–97)

86. **What is a queue?** A FIFO structure: insert at the rear, delete at the front.
87. **`front` and `rear`?** `front` = next element to delete; `rear` = last inserted element.
88. **Queue overflow/underflow?** Enqueue when full / dequeue when empty.
89. **Main drawback of a linear queue?** False overflow — freed slots at the front cannot be reused.
90. **How does a circular queue fix it?** `rear = (rear+1) % MAX` and `front = (front+1) % MAX` wrap the indices.
91. **Full condition for a circular queue?** `(rear + 1) % MAX == front`.
92. **Why might one slot be wasted?** In the `front = rear = 0` convention, one slot must stay free to distinguish full from empty.
93. **How can all slots be used?** Keep a separate `count`; full when `count == MAX`.
94. **Output order of a circular queue?** Start at `front`, wrap, stop after printing `rear`.
95. **Stack vs queue?** LIFO with one end vs FIFO with two ends.
96. **Can a queue be built from two stacks?** Yes — enqueue on S1; dequeue from S2, refilling S2 from S1 when empty.
97. **Applications of queues?** Printer spooling, CPU scheduling, keyboard buffers, BFS, call centres.

---

## H. Linked lists (98–117)

98. **What is a linked list?** A chain of nodes, each holding data and a pointer to the next, stored non-contiguously and reached via `head`.
99. **What does the last node point to?** `NULL` in a singly linked list.
100. **Why is `head` important?** It is the only entry point; losing it loses the whole list.
101. **Array vs linked list?** Array: O(1) random access, fixed size, shifting on insert/delete. List: O(n) access, dynamic size, O(1) insert/delete at a known position.
102. **Insert at beginning complexity?** O(1).
103. **Insert at end complexity?** O(n) without a tail pointer, O(1) with one.
104. **Search complexity?** O(n).
105. **Why can't we binary search a linked list?** No O(1) access to the middle.
106. **Steps to insert at the front?** `new->next = head; head = new;`
107. **Why save `current->next` before reversing?** Because `current->next = prev` overwrites the only link to the rest of the list.
108. **How to reverse a list?** Three pointers (`prev`, `current`, `next`), reverse each link in one pass, then `head = prev`.
109. **How to find the middle in one pass?** Slow/fast pointers; when fast reaches the end, slow is at the middle.
110. **How to detect a cycle?** Floyd's algorithm — if slow and fast ever meet, there is a cycle.
111. **What is a dummy/header node?** A data-less node before the first element that removes special cases and keeps `head` fixed.
112. **`Node *head` vs `Node **head`?** The second passes the address of the head pointer so the function can change which node is first.
113. **What is a circular linked list?** The last node points back to the first, forming a ring.
114. **How do you traverse a circular list?** `do { ... p = p->next; } while (p != head);`
115. **Why is a circular list useful?** Round-robin scheduling, playlists on repeat, token rings — anything cyclic.
116. **How is a polynomial stored in a linked list?** One node per non-zero term: coefficient, exponent, next; kept in descending exponent order.
117. **Polynomial addition complexity?** O(m+n) by merging two sorted lists.

---

## I. Tricky / scenario questions (118–132)

118. **Delete a node when you have only a pointer to it (not the head).** Copy the next node's data into it, then delete the next node. (Fails if it is the last node.)
119. **Find the k-th node from the end in one pass.** Two pointers `k` apart; advance both until the first hits `NULL`.
120. **Detect and remove a loop.** Detect with Floyd's algorithm, find the loop's start, then set the previous node's `next` to `NULL`.
121. **Merge two sorted linked lists?** Repeatedly take the smaller head of the two lists and append it. O(m+n).
122. **Reverse a list in groups of k?** Reverse `k` nodes at a time recursively/iteratively, linking each group to the next.
123. **Which is faster: array or linked list traversal?** Array — contiguous memory and CPU cache locality.
124. **Why is insertion in an array O(n) but in a list O(1)?** Array insertion shifts all later elements; a list only changes pointers (once the position is found).
125. **Your program crashes after `free(p); p->next = ...` — why?** Use-after-free: `p` is dangling. Save `next` before freeing.
126. **Your list prints forever — why?** Missing `p = p->next`, or a circular list whose termination check is wrong.
127. **Your binary search returns wrong results — why?** The array was not sorted.
128. **Matrix multiplication prints garbage — why?** `C[i][j]` was not initialised to 0 before accumulating.
129. **Postfix evaluation gives `-5` instead of `5` for `8 3 -` — why?** The operands were popped in the wrong order; pop the right operand first.
130. **Circular queue says full with empty slots — why?** The full test must be `(rear+1)%MAX == front`, and the display must start at `front`.
131. **Sparse addition result has a zero triplet — why?** Terms cancelled; skip insertion when the sum is 0.
132. **Difference between a bug and undefined behaviour?** A bug is wrong logic; UB means the C standard imposes no requirements (e.g. out-of-bounds access), so anything can happen.

---

## J. How to behave in the viva

1. **Listen to the whole question** before answering. Examiners often give a hint in the wording.
2. **Answer in one sentence first**, then elaborate if asked. Long rambling answers invite more questions.
3. **Use the data structure's vocabulary**: node, head, top, front, rear, pointer, overflow, underflow, complexity.
4. **Draw.** If a pointer question confuses you, ask for paper and draw boxes and arrows. Examiners reward this.
5. **Trace with a small example.** "With 3 elements, this happens…" proves understanding.
6. **Admit gaps honestly.** "I haven't implemented that, but I would…" is fine. Bluffing is not.
7. **Never say "the code does it"** — say *why* the code does it.
8. **If you wrote it, own it.** Be ready to explain any line the examiner points at. Read your own code once before the viva.
9. **Mention complexity voluntarily** on algorithm questions — it is free marks.
10. **Stay calm if you blank.** Start with the definition, then the operations, then an example. Answers usually come back.

---

## K. The five definitions you must never get wrong

- **Data structure** — a way of organising data in memory so it can be used efficiently.
- **Algorithm** — a finite, step-by-step procedure to solve a problem.
- **Stack** — LIFO, one end.
- **Queue** — FIFO, two ends.
- **Linked list** — nodes in non-contiguous memory linked by pointers.

---

**Next:** `11_CHEATSHEET.md`
