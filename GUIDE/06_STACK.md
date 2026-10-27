# 06 — Stack: Infix → Postfix and Postfix Evaluation

**Files:** `stack.c`, `stack2.c`
**Exam value:** very high. "Convert infix to postfix" and "evaluate postfix" are two of
the most frequently asked stack questions.

---

## 1. What is a stack?

A **LIFO** (Last In, First Out) structure. The last element pushed is the first popped.

```
            push  ->  +-------+
                      |   30  |  <- top
                      +-------+
                      |   20  |
                      +-------+
                      |   10  |
                      +-------+
                        stack
            <- pop
```

Real-life examples: a pile of plates, the undo history in an editor, the browser back
button, the call stack of function calls.

**Operations (all O(1)):**

| Operation | Meaning |
|-----------|---------|
| `push(x)` | add `x` on top |
| `pop()` | remove and return the top |
| `peek()` / `top()` | look at the top without removing |
| `isEmpty()` | `top == -1` |
| `isFull()` | `top == MAX - 1` |

**Conditions:**

- **Stack overflow** — push when `top == MAX-1` (array full).
- **Stack underflow** — pop when `top == -1` (empty).

---

## 2. Array implementation

Your files use this. It is the version to write in the exam.

```c
#define MAX 100

int stack[MAX];
int top = -1;          /* -1 means empty. This initialisation is worth a mark. */

void push(int value)
{
    if (top == MAX - 1)
        printf("Stack Overflow\n");
    else
        stack[++top] = value;    /* increase top, then store */
}

int pop()
{
    if (top == -1)
    {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack[top--];        /* return, then decrease top */
}
```

**Understand `stack[++top] = value;`** — two steps:
`top` becomes `top + 1`, then `stack[top] = value`.
`return stack[top--];` — return `stack[top]`, then `top` becomes `top - 1`.

```
Initially: top = -1

push(10): top = 0, stack[0] = 10
push(20): top = 1, stack[1] = 20
pop():    returns stack[1]=20, top = 0
```

**Algorithm (exam form):**

```
Algorithm: Push(S, top, MAX, x)
Step 1: Start
Step 2: if top = MAX-1 then
Step 3:     print "Stack Overflow"
Step 4: else
Step 5:     top = top + 1
Step 6:     S[top] = x
Step 7: end if
Step 8: Stop
```

```
Algorithm: Pop(S, top)
Step 1: Start
Step 2: if top = -1 then
Step 3:     print "Stack Underflow"
Step 4:     return -1
Step 5: else
Step 6:     x = S[top]
Step 7:     top = top - 1
Step 8:     return x
Step 9: end if
Step 10: Stop
```

**Linked-list stack (bonus answer):** push = insert at beginning (O(1)), pop = delete
first node (O(1)). It never overflows (until memory runs out) but uses extra memory for
pointers.

---

## 3. The three notations

Take the expression `A + B * C`.

| Notation | Form | Name |
|----------|------|------|
| Infix | `A + B * C` | operator **in** between operands |
| Postfix | `A B C * +` | operator **after** its operands (Reverse Polish) |
| Prefix | `+ A * B C` | operator **before** its operands (Polish) |

**Why postfix?** Computers cannot handle precedence and parentheses easily in infix.
Postfix needs **no parentheses and no precedence rules** — you just scan left to right
with a stack. It is also shorter to parse.

The infix expression `A + B * C` requires knowing `*` comes before `+`. In postfix,
`A B C * +` is unambiguous: the `*` always applies to the two values immediately before it.

---

## 4. Infix to postfix

### Rules

1. **Operand** (letter/digit) → send straight to output.
2. **`(`** → push it.
3. **`)`** → pop and output until `(` is found; discard the `(`.
4. **Operator** → while the stack is not empty, the top is not `(`, and the top's
   precedence is **≥** the current operator's precedence: pop to output. Then push the
   current operator.
5. **End of input** → pop everything remaining to output.

### Precedence and associativity

| Operator | Precedence | Associativity |
|----------|-----------|---------------|
| `^` | 3 (highest) | **Right** |
| `*`, `/` | 2 | Left |
| `+`, `-` | 1 (lowest) | Left |
| `(` | 0 (on stack only) | — |

### Algorithm `[MEMORISE]`

```
Algorithm: InfixToPostfix(infix, postfix)
Input : Infix expression as a string
Output: Equivalent postfix expression

Step 1: Start
Step 2: top = -1, j = 0
Step 3: for each character ch in infix do
Step 4:     if ch is an operand then
Step 5:         postfix[j] = ch, j = j + 1
Step 6:     else if ch = '(' then
Step 7:         push(ch)
Step 8:     else if ch = ')' then
Step 9:         while top != -1 and peek() != '(' do
Step 10:            postfix[j] = pop(), j = j + 1
Step 11:        end while
Step 12:        pop()                    // discard '('
Step 13:    else                        // ch is an operator
Step 14:        while top != -1 and precedence(peek()) >= precedence(ch) do
Step 15:            postfix[j] = pop(), j = j + 1
Step 16:        end while
Step 17:        push(ch)
Step 18:    end if
Step 19: end for
Step 20: while top != -1 do
Step 21:    postfix[j] = pop(), j = j + 1
Step 22: end while
Step 23: postfix[j] = '\0'
Step 24: Stop
```

**Time: O(n)** — every character is pushed and popped at most once.
**Space: O(n)** for the stack.

### Dry run 1: `A + B * C`

This is the classic confusion point: `*` has **higher** precedence than `+`, so we must
**not** pop `+`. The condition is "top precedence **≥** current precedence". Here
`prec(+) = 1`, `prec(*) = 2`, so `1 ≥ 2` is **false** → no pop → push `*`.

| ch | Action | Stack (bottom→top) | Output |
|----|--------|-------|--------|
| A | output | — | A |
| + | push | + | A |
| B | output | + | A B |
| * | prec(+) = 1 ≥ 2? **no** → push | + * | A B |
| C | output | + * | A B C |
| end | pop `*`, then `+` | — | **A B C * +** |

✓ Correct: `A B C * +`.

### Dry run 2: `A + B * (C - D)` — with brackets

| ch | Action | Stack | Output |
|----|--------|-------|--------|
| A | output | — | A |
| + | push | + | A |
| B | output | + | A B |
| * | 1 ≥ 2? no → push | + * | A B |
| ( | push | + * ( | A B |
| C | output | + * ( | A B C |
| − | top is `(` → push | + * ( − | A B C |
| D | output | + * ( − | A B C D |
| ) | pop until `(` → output `−`, discard `(` | + * | A B C D − |
| end | pop `*`, then `+` | — | **A B C D − * +** |

✓ Correct.

### ⚠️ The `^` associativity bug in `stack.c`

`^` is **right-associative**: `2^3^2` means `2^(3^2) = 2^9 = 512`, whose postfix is
`2 3 2 ^ ^`.

But the code uses `precedence(peek()) >= precedence(ch)` for **all** operators, so when
it sees the second `^` it pops the first one, producing `2 3 ^ 2 ^` — which is
`(2^3)^2 = 64`. **Wrong.**

Fix:

```c
while (top != -1 && peek() != '(' &&
       (precedence(peek()) > precedence(ch) ||
        (precedence(peek()) == precedence(ch) && ch != '^')))
{
    postfix[j++] = pop();
}
```

In words: pop when the top binds **more tightly**, or binds equally tightly and the
operator is **left-associative**. For `^`, equal precedence does not cause a pop.

Mentioning this in viva is a strong signal that you understand associativity, not just
the code.

### Other limits of `stack.c`
- It reads with `scanf("%s", infix)`, so the expression cannot contain spaces. That is
  fine for exams; use `fgets` if spaces are allowed.
- `isalnum` treats `1` and `2` in `12` as two separate operands. Single-character
  operands only. State this assumption.
- No check for mismatched brackets. `A+(B*C` silently produces output with a leftover `(`.

---

## 5. Postfix evaluation

### The idea

Scan left to right:

- **Operand** → push its value.
- **Operator** → pop two values, apply the operator, push the result.

At the end, the single value on the stack is the answer.

**Order matters for `−` and `/`:**

```c
operand2 = pop();       /* right operand, popped FIRST */
operand1 = pop();       /* left operand */
result = operand1 - operand2;
```

Popping `operand2` first is not a typo: the top of the stack is the **right-hand**
operand because it was pushed last. Reversing them turns `8 3 -` (= 5) into `3 - 8` (= −5).
**This is the single most common mistake in this program.** Your `stack2.c` gets it right
(lines 51–52).

### Algorithm `[MEMORISE]`

```
Algorithm: EvaluatePostfix(expression)
Input : Postfix expression
Output: Numeric value of the expression

Step 1: Start
Step 2: top = -1
Step 3: for each character ch in expression do
Step 4:     if ch is a digit then
Step 5:         push(ch - '0')             // convert character to number
Step 6:     else if ch is an operator then
Step 7:         operand2 = pop()
Step 8:         operand1 = pop()
Step 9:         result = apply(ch, operand1, operand2)
Step 10:        push(result)
Step 11:    end if
Step 12: end for
Step 13: return pop()
Step 14: Stop
```

**Time: O(n). Space: O(n).**

### Dry run: `2 3 + 4 *`  →  (2+3)*4 = 20

| ch | Action | Stack (bottom→top) |
|----|--------|--------------------|
| 2 | push 2 | 2 |
| 3 | push 3 | 2 3 |
| + | pop 3, pop 2 → 2+3=5, push | 5 |
| 4 | push 4 | 5 4 |
| * | pop 4, pop 5 → 5*4=20, push | 20 |
| end | pop → **20** | empty |

### Dry run: `5 3 - 8 2 - *`  →  (5−3)*(8−2) = 16

| ch | Action | Stack |
|----|--------|-------|
| 5 | push | 5 |
| 3 | push | 5 3 |
| − | 5−3 = 2 | 2 |
| 8 | push | 2 8 |
| 2 | push | 2 8 2 |
| − | 8−2 = 6 | 2 6 |
| * | 2*6 = 12 | 12 |

**Answer: 12.** `(5−3)*(8−2) = 2 × 6 = 12`.

### How `stack2.c` works

| Lines | What |
|-------|------|
| 10–16 | `push` with overflow check |
| 19–28 | `pop` with underflow check, returns −1 |
| 36–41 | skip spaces |
| 43–46 | `isdigit` → `push(ch - '0')` |
| 48–78 | operator: pop two, `switch`, push result |
| 90 | `fgets` reads the whole line (spaces allowed) |

`ch - '0'` converts a **character digit** to its numeric value: `'7' - '0' = 55 - 48 = 7`.
That is a classic viva question.

**Limits to state:**
- Only single-digit operands. `12 3 +` is read as `1, 2, 3, +`.
  Fix: accumulate digits into a number until a non-digit/space appears.
- No division-by-zero check. Add:
  `if (operand2 == 0) { printf("Division by zero\n"); return -1; }`
- No check that exactly one value remains at the end (malformed input).

---

## 6. Bonus: balanced parentheses (a classic viva task)

```
Algorithm: CheckBalanced(expression)
Step 1: Start
Step 2: top = -1
Step 3: for each ch in expression do
Step 4:     if ch = '(' or ch = '[' or ch = '{' then push(ch)
Step 5:     else if ch is a closing bracket then
Step 6:         if stack is empty then return false
Step 7:         if popped bracket does not match ch then return false
Step 8:     end if
Step 9: end for
Step 10: if stack is empty then return true else return false
Step 11: Stop
```

The stack remembers the **most recent** unclosed bracket, which is exactly the one that
must be closed first. That is why LIFO fits brackets.

---

## 7. Applications of stacks (viva favourite)

1. Expression conversion (infix → postfix/prefix) and evaluation.
2. **Function calls and recursion** — each call's local variables and return address are
   stored in a stack frame. This is why infinite recursion causes a "stack overflow".
3. Undo/redo in editors.
4. Browser back/forward history.
5. Balanced bracket checking and syntax parsing.
6. Depth-first search and backtracking (maze solving, N-Queens).
7. Converting decimal to binary (repeatedly push remainders, then pop).
8. Reversing a string or a linked list.

---

## Viva — stack

**Q1. Define a stack.**
A linear data structure that follows LIFO: insertion and deletion happen only at one end,
called the top.

**Q2. What are the primary operations?**
`push` (insert at top) and `pop` (delete from top), plus `peek`/`top`, `isEmpty`,
`isFull`. All are O(1).

**Q3. What is stack overflow / underflow?**
Overflow = push when the stack is full (`top == MAX-1`).
Underflow = pop when the stack is empty (`top == -1`).

**Q4. Why is `top` initialised to `−1`?**
So that the first `push` makes it 0, the index of the first element. `−1` cleanly means
"empty".

**Q5. Difference between stack and queue?**
Stack is LIFO with one open end; queue is FIFO with insertion at the rear and deletion
at the front.

**Q6. Difference between infix, postfix and prefix?**
Infix: operator between operands (`A+B`). Postfix: operator after (`AB+`). Prefix:
operator before (`+AB`).

**Q7. Why is postfix preferred by compilers?**
No parentheses and no precedence rules are needed; it can be evaluated in one left-to-right
pass with a stack.

**Q8. Give the postfix form of `A+B*C`.**
`A B C * +`.

**Q9. Give the postfix form of `(A+B)*C`.**
`A B + C *`. Compare with Q8: the brackets force the addition to happen first.

**Q10. Trace infix to postfix for `A-(B+C)*D/E`.**
`A B C + D * E / -`. (Verify: `(B+C)*D/E` is computed first, then subtracted from A.)

**Q11. Which data structure converts infix to postfix?**
A stack of operators.

**Q12. Which data structure evaluates postfix?**
A stack of operands (values).

**Q13. In postfix evaluation, in which order do you pop the two operands?**
Right operand first (it is on top), then left operand.

**Q14. Evaluate `5 3 2 * +`.**
`3*2 = 6`, then `5+6 = 11`.

**Q15. What is the time complexity of infix to postfix?**
O(n), because each character is pushed and popped at most once.

**Q16. How is recursion implemented?**
Using the system call stack: each call gets a stack frame with parameters, locals and the
return address. Unwinding pops frames.

**Q17. Can a stack be implemented with a linked list?**
Yes. Push = insert at the head, pop = delete the head, both O(1). It grows dynamically
but needs memory for pointers.

**Q18. How do you reverse a string using a stack?**
Push every character, then pop them all into a new string — LIFO reverses the order.

**Q19. What does `ch - '0'` do?**
Converts a digit character to its integer value (`'7' − '0' = 7`) using ASCII codes.

**Q20. What is the associativity of `^` and why does it matter?**
Right-associative: `2^3^2 = 2^(3^2)`. During conversion, an operator of equal precedence
is **not** popped when the incoming operator is `^`.

---

## Traps checklist

- [ ] `top = -1` at declaration.
- [ ] Check overflow **before** pushing, underflow **before** popping.
- [ ] `stack[++top]` on push, `stack[top--]` on pop.
- [ ] Pop the **right** operand first in evaluation.
- [ ] `precedence('(') = 0` so it is never popped by the precedence rule.
- [ ] On `)`, discard the `(` after popping.
- [ ] Pop the remaining operators at the end of the scan.
- [ ] Null-terminate the output string: `postfix[j] = '\0';`.
- [ ] For `^`, handle right associativity.

---

**Next:** `07_QUEUE.md`
