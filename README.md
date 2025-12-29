# Advanced C Programming Collection

A curated collection of low-level engineering challenges focused on pointer mastery, memory efficiency, and system-near logic.

## 📂 Repository Structure
This repository contains several specialized modules:
- **01-Data-Hiding-Techniques:** Steganography (LSB) and exploiting memory padding.
- **02-Maze-Pathfinder:** Recursive backtracking and pathfinding algorithms.
- **03-Circular-Buffer:** High-performance ring buffer for streaming data.
- **04-Custom-IO-Library:** Re-implementation of `printf` and `scanf` using variadic functions.
- **05-Doubly-Linked-List:** Dynamic bidirectional data structure management.
- **06-Generic-Sort-Implementation:** Callback-based sorting mimicking `qsort`.

## 🛠 Engineering Principles
- **No `[]` Operator:** All memory access is performed via raw pointer arithmetic.
- **Memory Safety:** Every module is validated for memory leaks using Valgrind.
- **Generic Programming:** Extensive use of `void *` and function pointers for type-agnostic logic.

## 🚀 How to Use
Each folder is self-contained with its own source files and headers. To compile any module:
`gcc main.c module_name.c -o output`
