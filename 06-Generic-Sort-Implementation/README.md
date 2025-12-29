# Generic Sort & Memory Manipulation

A low-level C implementation of a generic sorting algorithm (callback-based) that mimics the behavior of the standard library `qsort`.

## 🛠 Technical Highlights
- **Generic Data Handling:** The sorting function operates on `void *` buffers, allowing it to sort any data type (integers, floating-point numbers, or custom structures).
- **Function Pointers (Callbacks):** Implements a flexible comparison mechanism using custom comparator functions.
- **Strict Pointer Arithmetic:** Entirely avoids the `[]` operator. All memory offsets and element access are calculated manually using `(unsigned char *)base + (index * size)`.
- **Custom Data Structures:** Includes a specialized comparator for `point_t` structures with multi-level sorting logic (X-axis primary, Y-axis secondary).

## 🧩 Key Components
- `sort`: The core engine that swaps memory blocks of arbitrary size using `memcpy`-style logic.
- `comparators`: A library of type-specific logic for `int`, `double`, and `point_t`.
- **Dynamic Memory:** Efficient use of `malloc` and `free` with robust validation of heap allocation.

## 📊 Demonstrated Skills
- **Pointer Mastery:** Manual calculation of memory addresses in generic buffers.
- **Abstraction:** Decoupling the sorting algorithm from the data type it processes.
- **Error Resilience:** Validation of user input, array sizes, and memory availability with specific exit codes (2, 8, 1).



## 🚀 How to Run
1. Compile the source: `gcc main.c comparators.c -o generic_sort`
2. Run the application: `./generic_sort`
3. Select data type (0-int, 1-double, 2-point) and enter the array size.