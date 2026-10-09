# Experiment 5: Source Code Optimization

**Course Outcome:** CO5

## Aim
To demonstrate source code optimization using:
1. Operator Strength Reduction
2. Dead Code Elimination
3. Frequency Reduction / Loop-Invariant Code Motion

## Theory / Background
Code optimization improves intermediate or target code without changing program semantics. Three classical machine-independent optimization techniques are demonstrated:

### A. Operator Strength Reduction
Replaces a computationally expensive operation with an equivalent cheaper operation.
* **Before:**
  ```c
  x = i * 2;
  ```
* **After:**
  ```c
  x = i + i;
  ```

### B. Dead Code Elimination
Removes computations whose results are never used or cannot affect the observable output.
* **Before:**
  ```c
  int a = 10;
  int b = 20;
  int c = a + b;
  int x = 100;
  printf("%d", c);
  ```
* **After:**
  ```c
  int a = 10;
  int b = 20;
  int c = a + b;
  printf("%d", c);
  ```
  *(Variable `x` is assigned but never used, so its declaration and assignment are dead code and safely removed).*

### C. Frequency Reduction / Loop-Invariant Code Motion
Moves computations that do not depend on the loop variable outside of the loop.
* **Before:**
  ```c
  for (i = 0; i < 100; i++) {
      x = a * b;
      y = x + i;
  }
  ```
* **After:**
  ```c
  x = a * b;
  for (i = 0; i < 100; i++) {
      y = x + i;
  }
  ```
  *(`a * b` does not depend on `i`, so it is computed once before the loop instead of on every iteration).*

---

## Program Code (Illustrative C Program for Strength Reduction)
See [`optimization.c`](./optimization.c):

```c
#include <stdio.h>
#include <string.h>

int main()
{
    char expression[100];

    printf("Enter expression: ");
    fgets(expression, sizeof(expression), stdin);

    if (strstr(expression, "* 2") != NULL)
    {
        printf("\nOptimized expression:\n");
        printf("Replace multiplication by 2 with addition.\n");
        printf("x = i + i\n");
    }
    else
    {
        printf("\nNo strength reduction applicable.\n");
    }

    return 0;
}
```

## Sample Input & Output
```text
Enter expression: x = i * 2

Optimized expression:
Replace multiplication by 2 with addition.
x = i + i
```

---

## Viva-Voce Questions & Answers

**Q1. What is strength reduction?**  
> **Ans:** Replacing a computationally expensive operation with an equivalent cheaper operation, when doing so is valid (e.g., replacing multiplication by 2 with addition or left shift).

**Q2. What is dead code?**  
> **Ans:** Code whose result cannot affect the observable output of the program and can therefore be removed.

**Q3. What is loop-invariant code motion?**  
> **Ans:** An optimization that moves computations whose value does not change across loop iterations to outside the loop, reducing repeated work.