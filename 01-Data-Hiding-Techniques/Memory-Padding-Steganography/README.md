# Memory Padding Steganography

A low-level C project that demonstrates how to hide and retrieve secret messages within the unused "padding" bytes of data structures, caused by memory alignment.

## 🛠 Technical Highlights
- **Exploiting Alignment Padding:** The project targets the gaps in a `struct message_t` (char, double, int). Due to compiler alignment, only 13 out of 24 bytes are used for data, leaving 11 "hidden" bytes per structure.
- **Raw Memory Access:** Uses pointer arithmetic to navigate through the exact byte offsets where the compiler inserts padding.
- **Binary File Parsing:** Implementation of a robust binary loader that validates data integrity (ensuring file size is a multiple of structure size).
- **Strict Pointer Arithmetic:** Entirely avoids the `[]` operator, using manual address calculation to access memory.



## 🧩 Key Functions
- `load_data`: Reads binary data into an array of structures, validating the input stream and handling partial reads.
- `decode_message`: Scans the memory block occupied by the structures, extracts data from the "dead zones" (padding), and reconstructs the hidden text.

## 📊 Performance & Scalability
- **Efficiency:** The decoding algorithm has $O(n)$ complexity, where $n$ is the number of structures.
- **Capacity:** In an array of 100 structures (2400 bytes total), the system can hide up to **1100 bytes** of secret text without altering the visible data fields (`char a`, `double b`, `int c`).

## 📋 Demonstrated Skills
- **Deep Memory Awareness:** Understanding how compilers align data for 64-bit/32-bit architectures.
- **Pointer-Based Logic:** Navigating complex memory maps using `(const char *)ptr` and offsets.
- **Data Integrity:** Implementing error codes for corrupted files (-3) and missing resources (-2).



## 🚀 Usage Example
1. Prepare a binary file with hidden data in padding zones.
2. Compile: `gcc main.c -o padding_decoder`
3. Run: `./padding_decoder`
4. Enter the filename to extract the hidden quote/message.