# 03 — Searching: Linear and Binary

**Files:** `Searching_sorting.c`
**Code snippets:** the old standalone `linear_search.c` / `binary_search.c` are in the git history; the same logic now lives in `Searching_sorting.c`.
**One-line difference:** linear search checks every element; binary search throws away
half the array each step — but **only works on sorted data**.

---

## Comparison at a glance

| | Linear Search | Binary Search |
|---|---|---|
| Precondition | none | array **must be sorted** |
| Idea | check one by one | check middle, discard half |
| Best case | O(1) (first element) | O(1) (middle element) |
| Average | O(n/2) = O(n) | O(log₂ n) |
| Worst | O(n) | O(log₂ n) |
| Space | O(1) | O(1) iterative, O(log n) recursive (stack) |
| Works on linked list? | yes | no (no random access) |
| Use when | small / unsorted data | large sorted data |

For 1,000,000 elements: linear ≈ 1,000,000 checks, binary ≈ **20**.

---

# Part A — Linear search

## The idea

Start at index 0, compare each element with the key. Found → return the index.
Reached the end without finding → return −1.

```
Array:  [ 10 | 23 | 45 | 70 | 82 ]
Key = 45

check 10  -> no
check 23  -> no
check 45  -> MATCH at index 2
```

## Algorithm `[MEMORISE]`

```
Algorithm: LinearSearch(A, n, key)
Input : Array A of n elements and the key to be searched
Output: Index of key if found, otherwise -1

Step 1: Start
Step 2: for i = 0 to n-1 do
Step 3:     if A[i] = key then
Step 4:         return i
Step 5:     end if
Step 6: end for
Step 7: return -1
Step 8: Stop
```

**Complexity:** best O(1), worst O(n), average O(n). Space O(1).

## Code (linear-search pattern)

```c
for (i = 0; i < n; i++)
{
    if (arr[i] == key)
    {
        printf("Element found at position %d", i + 1);
        found = 1;
        break;          /* stop searching */
    }
}
if (found == 0)
    printf("Element not found");
```

Notes:

- `break` matters. Without it you keep scanning after finding the key (slow, and could
  print multiple positions).
- `i + 1` converts a 0-based index to a human "position" (1st, 2nd, …).
- The `found` flag is needed because after the loop `i` may equal `n` either because
  the element was not found or because it was found at the last position — but with
  `break` those differ. A flag is the clearest.

**Cleaner version returning an index (write this in the exam):**

```c
int linearSearch(int a[], int n, int key)
{
    int i;
    for (i = 0; i < n; i++)
        if (a[i] == key)
            return i;

    return -1;
}
```

If the question says "use a function", return the index and let `main` print. That is
better style than printing inside the search function.

## Dry run

`A = {10, 23, 45, 70, 82}`, `key = 45`

| i | A[i] | A[i] == key? |
|---|------|--------------|
| 0 | 10 | no |
| 1 | 23 | no |
| 2 | 45 | **yes → return 2** |

`key = 99` → i goes 0…4, loop ends, return −1.

---

# Part B — Binary search

## The idea

Imagine a dictionary. To find "M", you open the middle. If you see "P", the word must
be earlier, so you ignore the entire second half. Repeat.

**Two conditions:**

1. The array **must be sorted**.
2. You can jump to the middle instantly (arrays can; linked lists cannot).

```
Sorted: [ 10 | 23 | 45 | 70 | 82 ]      key = 70

low=0                 high=4
mid = (0+4)/2 = 2  -> A[2] = 45 < 70  -> search right: low = 3

low=3  high=4
mid = (3+4)/2 = 3  -> A[3] = 70 = 70  -> FOUND at index 3
```

## Algorithm (iterative) `[MEMORISE]`

```
Algorithm: BinarySearch(A, n, key)
Input : Sorted array A of n elements and the key
Output: Index of key if found, otherwise -1

Step 1: Start
Step 2: low = 0, high = n - 1
Step 3: while low <= high do
Step 4:     mid = (low + high) / 2
Step 5:     if A[mid] = key then
Step 6:         return mid
Step 7:     else if A[mid] < key then
Step 8:         low = mid + 1
Step 9:     else
Step 10:        high = mid - 1
Step 11:    end if
Step 12: end while
Step 13: return -1
Step 14: Stop
```

**Complexity:** best O(1), worst/average **O(log₂ n)**. Space O(1).

**Why `low <= high` and not `<`?** When `low == high` there is still exactly one element
left to check. Using `<` would skip it and miss the key when it is the last candidate.

**Why `low = mid + 1` and not `low = mid`?** Because `mid` itself was already checked.
Not advancing causes an infinite loop.

## Recursive version (they may ask)

```
Algorithm: BinarySearchRec(A, low, high, key)
Step 1: Start
Step 2: if low > high then return -1
Step 3: mid = (low + high) / 2
Step 4: if A[mid] = key then return mid
Step 5: else if A[mid] < key then
Step 6:     return BinarySearchRec(A, mid+1, high, key)
Step 7: else
Step 8:     return BinarySearchRec(A, low, mid-1, key)
Step 9: end if
Step 10: Stop
```

```c
int binarySearchRec(int a[], int low, int high, int key)
{
    if (low > high)
        return -1;

    int mid = (low + high) / 2;

    if (a[mid] == key)
        return mid;
    if (a[mid] < key)
        return binarySearchRec(a, mid + 1, high, key);
    return binarySearchRec(a, low, mid - 1, key);
}
```

Recursion adds O(log n) **stack space**. The iterative version is O(1) space — say this
in viva, it is exactly the kind of comparison examiners like.

## Dry run table (best for Part C)

`A = {10, 23, 45, 70, 82}`, `key = 23`

| Step | low | high | mid | A[mid] | Action |
|------|-----|------|-----|--------|--------|
| 1 | 0 | 4 | 2 | 45 | 45 > 23 → `high = 1` |
| 2 | 0 | 1 | 0 | 10 | 10 < 23 → `low = 1` |
| 3 | 1 | 1 | 1 | 23 | **found at index 1** |

## How your files implement it

The old standalone `binary_search.c` (git history) was a whole program in `main` that assumed sorted input.
Correct `while (low <= high)` loop.

`Searching_sorting.c` — same logic but on an **array of structs**, comparing
`s[mid].roll` instead of `s[mid]`:

```c
if (s[mid].roll == key) return mid;
else if (s[mid].roll < key) low = mid + 1;
else high = mid - 1;
```

That is the right way to generalise search: **search by a key field**, not by the whole
record. Viva answer: *"For records, we compare one field (the roll number) and return
the index of the matching record."*

**⚠️ Bug in `Searching_sorting.c`:** the menu lets you choose *Binary Search* (option 6)
even if the list has never been sorted. Binary search on unsorted data returns wrong
answers silently. Fix: either call a sort before binary search, or refuse with
`printf("Sort the list first.\n");`. Mention this in viva and you look like you
understand the precondition, not just the code.

---

## Viva — searching

**Q1. What is searching?**
Finding the position of a given element (the key) in a collection.

**Q2. Which search is better?**
Binary — O(log n) vs O(n) — **but only on sorted data**. If data is unsorted and will be
searched only once, linear search is better because sorting costs O(n log n) first.

**Q3. Why must the array be sorted for binary search?**
The algorithm decides to discard the left or right half by comparing with `A[mid]`. That
decision is only valid if elements are ordered.

**Q4. Can binary search be applied to a linked list?**
No. It needs direct access to the middle element (`A[mid]`) in O(1); a linked list
requires walking from the head, which destroys the O(log n) advantage.

**Q5. What are `low`, `high` and `mid`?**
The current search window's first index, last index, and middle index.

**Q6. What happens if `low` becomes greater than `high`?**
The search window is empty → the key is not present → return −1.

**Q7. Why is binary search O(log n)?**
Each comparison halves the remaining elements: `n → n/2 → n/4 → … → 1`, which takes
`log₂ n` steps.

**Q8. Best and worst case of linear search?**
Best O(1) (first element), worst O(n) (last element or absent).

**Q9. What is a sentinel search?**
A linear search optimisation: put the key at the end of the array so the loop does not
need a bounds check every iteration. Reduces comparisons by about half.

**Q10. What is the difference between `return -1` and returning `n`?**
Both can mean "not found"; −1 is conventional because it can never be a valid index.

**Q11. What is interpolation search?**
A variant for uniformly distributed sorted numeric data; estimates the position instead
of taking the middle. Average O(log log n), worst O(n).

**Q12. Which is better for 10 elements?**
Linear. Binary's overhead isn't worth it at that size, and sorting may cost more.

---

## Traps checklist

- [ ] Binary search: array **is sorted** (state this assumption in your answer!).
- [ ] `while (low <= high)`, not `<`.
- [ ] `low = mid + 1`, `high = mid - 1`.
- [ ] Linear search stops after the first match (`break` / `return`).
- [ ] Return `-1` when not found, and say so in the output message.
- [ ] For huge arrays, `mid = low + (high - low) / 2` avoids integer overflow — a nice
      one-line remark that impresses examiners.

---

**Next:** `04_SORTING.md`
