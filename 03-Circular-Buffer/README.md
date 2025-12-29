# Circular Buffer (Ring Buffer) Implementation

A high-performance C implementation of a Circular Buffer, optimized for real-time data streaming and efficient memory reuse.

## 🛠 Technical Highlights
- **Ring Architecture:** Implements a circular logic where the `end` pointer wraps around to the `begin` position when the capacity is reached, ensuring $O(1)$ complexity for both push and pop operations.
- **Dynamic Memory Management:** Features two allocation strategies:
    - `circular_buffer_create`: Initializes an existing structure.
    - `circular_buffer_create_struct`: Fully dynamic allocation of both the control structure and the data buffer.
- **Overwriting Logic:** In "Push Back" mode, if the buffer is full, the oldest data is automatically overwritten, making it ideal for logging or sensor data streams.
- **Bit-Field Optimization:** Uses a 1-bit bit-field (`unsigned char full: 1`) to minimize the memory footprint of the status flags.
- **Zero Operator `[]` Policy:** All memory interactions are handled via raw pointer arithmetic to demonstrate deep control over memory offsets.



## 📋 Features & API
- **Push/Pop Versatility:** Supports `push_back`, `pop_front` (Standard Queue behavior), and `pop_back` (Stack-like retrieval).
- **State Management:** Dedicated functions to check `empty` and `full` states.
- **Memory Safety:** Comprehensive `destroy` functions to prevent memory leaks in complex dynamic allocation scenarios.

## 🧠 Engineering Concept
A Circular Buffer is essential for decoupling data production from data consumption. By using two indices (`begin` and `end`), we avoid the expensive $O(n)$ data shifting required in standard arrays.



## 📊 Demonstrated Skills
- **Embedded Logic:** Handling buffer wrap-around using the modulo operator or conditional resets.
- **Low-Level Design:** Utilizing pointers to manage data flow without standard array indexing.
- **Robust Error Handling:** Validation of buffer consistency and heap availability (Exit codes 1, 2, 8).

## 🚀 Usage Example
```c
struct circular_buffer_t *cb;
circular_buffer_create_struct(&cb, 10);

circular_buffer_push_back(cb, 42);
int val = circular_buffer_pop_front(cb, &err_code); // val = 42

circular_buffer_destroy_struct(&cb);