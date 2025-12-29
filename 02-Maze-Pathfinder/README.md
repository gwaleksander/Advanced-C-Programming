# Recursive Maze Solver

A C-based application that finds a path between two points in a maze using a recursive backtracking algorithm.

## 🛠 Technical Highlights
- **Dynamic 2D Allocation:** The maze is loaded from a file into a dynamically allocated 2D array (`char ***`).
- **Pointer-Only Operations:** All array manipulations are performed using pointer arithmetic (no `[]` operator), demonstrating deep understanding of memory layout.
- **Backtracking Algorithm:** Implements a recursive search to find the exit (`b`) from the start (`a`).
- **Robust Error Handling:** Comprehensive validation of file integrity, memory allocation, and path existence with specific exit codes.

## 📋 Features
- **Automatic Maze Detection:** The program calculates maze dimensions (rows/cols) automatically before allocation.
- **Path Marking:** Successfully found paths are marked with `*` and displayed in the console.
- **Memory Safety:** Includes a dedicated `free_maze` function to ensure zero memory leaks (verified with Valgrind).

## 🚀 Usage
The program expects a text file where:
- `#` is a wall
- `a` is the start
- `b` is the exit
- ` ` is a path

Example execution:
`Enter filename: maze.txt`