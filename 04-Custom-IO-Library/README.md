# Custom I/O Library (printf & scanf Re-implementation)

A low-level implementation of `my_printf` and `my_scanf` functions, built entirely without using the standard C library's I/O functions.

## 🛠 Technical Highlights
- **Variadic Functions:** Advanced use of `<stdarg.h>` and `va_list` to handle a variable number of arguments.
- **Zero Standard Library Dependencies:** Implemented using low-level character-by-character output (e.g., via `putchar`) and manual parsing.
- **Strict Constraints:**
    - **No `[]` Operator:** Entirely pointer-based implementation.
    - **No Memory Allocation:** Zero heap usage, focusing on stack efficiency.
    - **Custom Format Specifier:** Support for a custom `%p` specifier to handle `point_t` structures directly.

## 📋 Features
- **my_printf:** - Supports `%s` (strings), `%d` (32-bit integers), `%f` (double precision with fixed 5-decimal accuracy), and `%p` (structured points).
    - Returns the exact count of characters displayed.
- **my_scanf:**
    - Robust parsing of integers, doubles (decimal format), and structured points in the format `(x y)`.
    - Returns the count of successfully parsed elements.

## 📊 Demonstrated Skills
- **Bit-to-String Conversion:** Manual implementation of integer-to-ascii (itoa) and float-to-string conversion logic.
- **Buffer Parsing:** Manual stream scanning and state-machine logic for format specifier detection.
- **Pointer Arithmetic:** Navigating and modifying memory directly via pointers to populate variables in `my_scanf`.



## 🚀 Usage Example
```c
struct point_t p;
int count = my_scanf("%p", &p); // Reads input like "(10 20)"
my_printf("Point coordinates: %p\n", p); // Outputs: (10 20)