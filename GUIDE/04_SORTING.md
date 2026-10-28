# 04 — Sorting: Bubble, Selection, Insertion, Shell

**Files:** `bubble_sort.c`, `Searching_sorting.c`
**Code snippets:** the old standalone `selection_sort.c` is in the git history; `Searching_sorting.c` now contains insertion, selection and shell sort.
**Exam value:** extremely high. "Write an algorithm to sort n numbers" is almost
guaranteed to appear in some form.

---

## The big picture

All four are **comparison sorts** and all four are **in-place** (only a few extra
variables). They differ in *how* they move elements.

| Algorithm | One-line idea | Best | Average | Worst | Stable? | Swaps |
|-----------|---------------|------|---------|-------|---------|-------|
| Bubble | repeatedly swap neighbours | O(n)* | O(n²) | O(n²) | **Yes** | O(n²) |
| Selection | repeatedly pick the smallest | O(n²) | O(n²) | O(n²) | No | **O(n)** |
| Insertion | insert each card in its place | **O(n)** | O(n²) | O(n²) | **Yes** | O(n²) |
| Shell | insertion sort on far-apart items | O(n log n) | ~O(n^1.3) | O(n²) | No | O(n²) |

\* only with the early-exit flag; the plain version is O(n²) even on sorted input.

**Stable** = equal elements keep their original relative order.
Important when sorting records by one field (e.g. sort students by marks, keeping
same-marks students in roll-number order).

**Which to choose?**

- Nearly sorted, small → **insertion sort** (fast, stable, simple).
- Minimum writes / flash memory → **selection sort**.
- Teaching / detecting "already sorted" → **bubble sort**.
- Medium-size general purpose, simple code → **shell sort**.
- Real work → quicksort / merge sort (`qsort()` in C), **not** these four.

---

# 1. Bubble Sort `[MEMORISE]`

## The idea

Compare adjacent pairs and swap if out of order. After one full pass, the **largest**
element has "bubbled" to the end. After pass 2, the second largest is in place, and so on.
After `n−1` passes everything is sorted.

```
Pass 1:  5  2  9  1  7
         2  5  9  1  7      (5>2 swap)
         2  5  9  1  7      (5<9 no)
         2  5  1  9  7      (9>1 swap)
         2  5  1  7  9      (9>7 swap)  -> 9 is now final
Pass 2:  2  1  5  7  9
Pass 3:  1  2  5  7  9
Pass 4:  (no swaps)  -> done
```

## Algorithm

```
Algorithm: BubbleSort(A, n)
Input : Array A of n elements
Output: Array A sorted in ascending order

Step 1: Start
Step 2: for i = 0 to n-2 do
Step 3:     for j = 0 to n-2-i do
Step 4:         if A[j] > A[j+1] then
Step 5:             swap A[j] and A[j+1]
Step 6:         end if
Step 7:     end for
Step 8: end for
Step 9: Stop
```

**Why `n-2-i`?** The last `i` elements are already sorted, and `j+1` must stay inside
the array, so the last valid `j` is `n-2-i`.

Complexity: O(n²) comparisons always; O(n²) swaps worst case. Space O(1). **Stable.**

## Code (`bubble_sort.c`)

```c
for (i = 0; i < n - 1; i++)              /* number of passes */
{
    for (j = 0; j < n - 1 - i; j++)      /* comparisons in this pass */
    {
        if (arr[j] > arr[j + 1])
        {
            temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
        }
    }
}
```

**Optimised version (mention this for bonus marks):**

```c
for (i = 0; i < n - 1; i++)
{
    int swapped = 0;
    for (j = 0; j < n - 1 - i; j++)
        if (arr[j] > arr[j + 1])
        {
            temp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = temp;
            swapped = 1;
        }

    if (!swapped)        /* no swaps -> already sorted */
        break;
}
```

This makes the **best case O(n)** on already-sorted input.

## Dry run (write this table in the exam)

`A = {5, 2, 9, 1, 7}`

| Pass i | After pass | Comment |
|--------|-----------|---------|
| 0 | 2 5 1 7 **9** | 9 fixed at the end |
| 1 | 2 1 5 **7 9** | 7, 9 fixed |
| 2 | 1 2 **5 7 9** | |
| 3 | **1 2 5 7 9** | no swaps, sorted |

---

# 2. Selection Sort `[MEMORISE]`

## The idea

Find the smallest element in the unsorted part and **swap** it into position `i`.
Only **one swap per pass** — that is its advantage.

```
5  2  9  1  7
^            find min in [0..4] = 1 at index 3 -> swap with index 0
1  2  9  5  7
   ^         find min in [1..4] = 2 at index 1 -> already there
1  2  9  5  7
      ^      find min in [2..4] = 5 at index 3 -> swap with index 2
1  2  5  9  7
         ^   find min in [3..4] = 7 at index 4 -> swap with index 3
1  2  5  7  9
```

## Algorithm

```
Algorithm: SelectionSort(A, n)
Input : Array A of n elements
Output: Array A sorted in ascending order

Step 1: Start
Step 2: for i = 0 to n-2 do
Step 3:     minIndex = i
Step 4:     for j = i+1 to n-1 do
Step 5:         if A[j] < A[minIndex] then
Step 6:             minIndex = j
Step 7:         end if
Step 8:     end for
Step 9:     if minIndex != i then
Step 10:        swap A[i] and A[minIndex]
Step 11:    end if
Step 12: end for
Step 13: Stop
```

Complexity: **O(n²) in all cases** (it always scans the rest, even if sorted).
Swaps: at most `n−1`. Space O(1). **Not stable** (a long-distance swap can jump an
equal element over its twin).

## Code (selection-sort pattern)

```c
for (i = 0; i < n - 1; i++)
{
    minIndex = i;

    for (j = i + 1; j < n; j++)
        if (arr[j] < arr[minIndex])
            minIndex = j;

    temp = arr[i];              /* the swap can be done unconditionally; */
    arr[i] = arr[minIndex];     /* the `if (minIndex != i)` is a small optimisation */
    arr[minIndex] = temp;
}
```

**Why `j = i + 1`?** Position `i` is the current candidate; there is no need to compare
it with itself.

---

# 3. Insertion Sort `[MEMORISE]`

## The idea

Exactly how you sort playing cards in your hand. Take the next card, and shift the
larger cards right until you find its place.

```
Start:   [5]  2  9  1  7        (first element is a sorted "hand" of one)

take 2:  [2  5]  9  1  7
take 9:  [2  5  9]  1  7
take 1:  [1  2  5  9]  7
take 7:  [1  2  5  7  9]
```

## Algorithm

```
Algorithm: InsertionSort(A, n)
Input : Array A of n elements
Output: Array A sorted in ascending order

Step 1: Start
Step 2: for i = 1 to n-1 do
Step 3:     key = A[i]
Step 4:     j = i - 1
Step 5:     while j >= 0 and A[j] > key do
Step 6:         A[j+1] = A[j]
Step 7:         j = j - 1
Step 8:     end while
Step 9:     A[j+1] = key
Step 10: end for
Step 11: Stop
```

Complexity: best **O(n)** (already sorted — the while loop never runs), worst O(n²)
(reverse sorted), average O(n²). Space O(1). **Stable.** Best of the three O(n²)
sorts in practice.

## Code (`Searching_sorting.c`)

```c
for (int i = 1; i < n; i++)
{
    struct Student temp = s[i];      /* save the whole record */
    int j = i - 1;

    while (j >= 0 && s[j].roll > temp.roll)
    {
        s[j + 1] = s[j];             /* shift right */
        j--;
    }

    s[j + 1] = temp;                 /* drop into the gap */
}
```

Notice: it copies **whole structs**, so the name moves with the roll number. If you
sorted only `roll`, the names would get mismatched. That is an important viva point.

### Trace: `{5, 2, 9, 1, 7}`

| i | key | Shifts | Array after |
|---|-----|--------|-------------|
| 1 | 2 | 5 → right | 2 5 9 1 7 |
| 2 | 9 | none | 2 5 9 1 7 |
| 3 | 1 | 9,5,2 → right | 1 2 5 9 7 |
| 4 | 7 | 9 → right | 1 2 5 7 9 |

### The one-line summary to say in viva
> "Insertion sort is adaptive: on nearly sorted data it runs in almost O(n), which is why
> it is used as the base case in quicksort and in library sort implementations."

---

# 4. Shell Sort

## The idea

Insertion sort is slow because an element can only move one position per comparison.
Shell sort first sorts elements that are **`gap` positions apart**, so a far-away element
can jump close to its final place in one move. Then it shrinks the gap and finally does
a normal insertion sort (`gap = 1`).

Gap sequence used in your code: `n/2, n/4, …, 1` (Shell's original sequence).

## Algorithm

```
Algorithm: ShellSort(A, n)
Input : Array A of n elements
Output: Array A sorted in ascending order

Step 1: Start
Step 2: gap = n / 2
Step 3: while gap > 0 do
Step 4:     for i = gap to n-1 do
Step 5:         temp = A[i]
Step 6:         j = i
Step 7:         while j >= gap and A[j-gap] > temp do
Step 8:             A[j] = A[j-gap]
Step 9:             j = j - gap
Step 10:        end while
Step 11:        A[j] = temp
Step 12:    end for
Step 13:    gap = gap / 2
Step 14: end while
Step 15: Stop
```

Complexity: depends on the gap sequence. With `n/2` halving it is O(n²) worst case, but
in practice far faster than O(n²) — roughly O(n^1.3) on average. With Knuth's sequence
`1, 4, 13, 40, …` it is O(n^1.5). Space O(1). **Not stable** (equal elements can be
separated by gap jumps).

## Code (`Searching_sorting.c`)

```c
for (int gap = n / 2; gap > 0; gap /= 2)
{
    for (int i = gap; i < n; i++)
    {
        struct Student temp = s[i];
        int j = i;

        while (j >= gap && s[j - gap].roll > temp.roll)
        {
            s[j] = s[j - gap];      /* shift by gap, not by 1 */
            j -= gap;
        }

        s[j] = temp;
    }
}
```

Compare with insertion sort: **`1` is replaced by `gap`**. That is the whole difference.
If you can write insertion sort, you can write shell sort.

### Trace: `{5, 2, 9, 1, 7}`, n = 5

**gap = 2**

| i | temp | Action | Array |
|---|------|--------|-------|
| 2 | 9 | A[0]=5 not > 9 | 5 2 9 1 7 |
| 3 | 1 | A[1]=2 > 1 → shift | 5 2 2 1 7 |
|   |    | place at index 1 | 5 1 9 2 7 |
| 4 | 7 | A[2]=9 > 7 → shift | 5 1 9 9 7 |
|   |    | place at index 2 | 5 1 7 2 9 |

**gap = 1** (normal insertion sort)

| i | temp | Array after |
|---|------|-------------|
| 1 | 1 | 1 5 7 2 9 |
| 2 | 7 | 1 5 7 2 9 |
| 3 | 2 | 1 2 5 7 9 |
| 4 | 9 | 1 2 5 7 9 |

---

## How `Searching_sorting.c` puts it together

This file is a **record management system**, not just a sort demo. It shows the pattern
you should reuse in the exam whenever the question mentions "students", "employees" or
"items":

```c
struct Student { int roll; char name[50]; float marks; };
struct Student s[MAX];
```

- `display()` — formatted table output (`%-10s` left-aligns in 10 columns).
- `linearSearch()` / `binarySearch()` — compare `s[i].roll`.
- `insertionSort()` / `selectionSort()` / `shellSort()` — swap whole structs, so the
  name and marks stay attached to the right roll number.

### ⚠️ One bug to know about

`selectionSort()` uses `if (min != i)` before swapping — harmless, just an optimisation.
But **`binarySearch()` is available in the menu without ensuring the list is sorted.**
Binary search on unsorted records gives wrong results with no error message. In an exam
demo, sort first (option 3/4/5) and *then* binary search.

Also note `scanf("%s", s[i].name)` cannot read a name containing a space. Use
`scanf(" %49[^\n]", s[i].name)` if the examiner enters a full name.

---

## Viva — sorting

**Q1. What is sorting?**
Arranging elements in a definite order (ascending or descending) according to some key.

**Q2. Which sort is fastest among these four?**
Shell sort in practice; insertion sort for small or nearly sorted data. All four are
beaten by quicksort/mergesort for large random data.

**Q3. What is an in-place algorithm?**
One that uses O(1) extra memory (only a few variables), rearranging inside the array
itself. All four here are in-place.

**Q4. What is a stable sort?**
One that preserves the relative order of equal elements. Bubble and insertion are
stable; selection and shell are not.

**Q5. Why does bubble sort need `n-1` passes?**
Each pass fixes one element at the end. After `n-1` passes, the remaining single element
is automatically in place.

**Q6. Why is selection sort's inner loop `j = i+1`?**
Because `A[i]` is the initial candidate for minimum; comparing it with itself is useless.

**Q7. Which sort performs the fewest swaps?**
Selection sort: at most `n−1` swaps. Useful when writes are expensive.

**Q8. Which sort is best for nearly sorted data?**
Insertion sort — O(n) when already sorted.

**Q9. Is insertion sort recursive?**
It can be written recursively, but the iterative version is simpler and uses O(1) space.

**Q10. What is the best case of bubble sort?**
O(n) **if** you add the `swapped` flag to stop early; O(n²) for the plain version.

**Q11. What is the difference between comparison sort and non-comparison sort?**
Comparison sorts order by comparing pairs (lower bound Ω(n log n)). Counting/radix/bucket
sorts use the values directly and can be O(n) for restricted ranges.

**Q12. What gap sequence does your shell sort use?**
`n/2, n/4, …, 1`. Other sequences (Knuth, Hibbard) give better theoretical bounds.

**Q13. Why is shell sort not stable?**
Because gap jumps can move an element past an equal element that it would not have
crossed in a plain insertion sort.

**Q14. How many comparisons does bubble sort make?**
`n(n−1)/2` in the worst case, so O(n²).

**Q15. Where are these used in real code?**
Insertion sort for tiny arrays inside `qsort`/Timsort; selection sort when swap cost
dominates; bubble sort essentially only in teaching.

---

## Traps checklist

- [ ] Bubble: inner loop bound `n-1-i`, and remember `j+1` must be valid.
- [ ] Selection: `minIndex` initialised to `i`, inner loop starts at `i+1`.
- [ ] Insertion: `temp` saves the element **before** shifting; place at `j+1`.
- [ ] Shell: compare with `A[j-gap]`, shift by `gap`, place at `j`.
- [ ] Sorting a struct array: move the **whole struct**, not one field.
- [ ] State whether you are sorting ascending or descending, and flip the comparison
      (`>` vs `<`) accordingly.
- [ ] In the algorithm, write `swap A[j] and A[j+1]` as one step (no need for `temp`).

---

**Next:** `05_SPARSE.md`
