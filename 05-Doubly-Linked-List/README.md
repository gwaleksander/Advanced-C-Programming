# Doubly Linked List (DLL) Implementation

A comprehensive, low-level C implementation of a Doubly Linked List, featuring bidirectional traversal and dynamic node management.

## 🛠 Technical Highlights
- **Bidirectional Navigation:** Each node maintains pointers to both the `next` and `previous` elements, allowing for efficient $O(1)$ removals at both ends and reverse iteration.
- **Full Lifecycle API:** Includes functions for creation, insertion at any index, removal, and complete memory cleanup (`dll_clear`).
- **Dynamic Node Management:** Demonstrated expertise in heap allocation (`malloc`/`free`) with strict error handling for allocation failures (Exit code 8).
- **Pointer-Only Architecture:** Adheres to strict constraints by avoiding the `[]` operator, relying entirely on manual pointer manipulation and structure traversal.



## 📋 Key Features & API
- **Insertion:** `push_back`, `push_front`, and `dll_insert` (at specific index).
- **Deletion:** `pop_back`, `pop_front`, and `dll_remove` (from specific index).
- **Access:** `dll_front`, `dll_back`, and `dll_at` for index-based data retrieval.
- **Visualization:** Two display modes: `dll_display` (head to tail) and `dll_display_reverse` (tail to head).
- **Metadata:** `dll_size` and `dll_is_empty` for real-time list monitoring.

## 🧠 Engineering Concept: DLL vs SLL
While a Singly Linked List (SLL) saves memory by using only one pointer per node, the **Doubly Linked List** implemented here allows for much faster deletions when the pointer to the node is already known, and enables the program to traverse data in both directions—crucial for features like "undo/redo" or browser history navigation.



## 📊 Demonstrated Skills
- **Manual Heap Management:** Balancing every `malloc` with a corresponding `free` to ensure zero memory leaks.
- **Edge Case Handling:** Professional management of empty lists, single-node lists, and boundary conditions (Index out of range).
- **Modular Library Design:** Clean separation between the data structure logic (`.h`/`.c`) and the interactive console interface.

## 🚀 Usage Example
```c
struct doubly_linked_list_t *list = dll_create();

dll_push_front(list, 10);
dll_push_back(list, 20);
dll_insert(list, 1, 15); // List: 10 15 20

dll_display(list);
dll_clear(list);
free(list);