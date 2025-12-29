# PNM/PGM Image Processing Engine

A robust C engine for manipulating raster graphics in the Portable Graymap (PGM) format. This tool supports complex operations like embedding multiple sub-images into a destination carrier with precise coordinate control.

## 🛠 Technical Highlights
- **Dynamic 2D Raster Mapping:** Implements an `image_t` structure managing a 2D pixel array via `int **ptr`, optimized for grayscale depth.
- **Image-in-Image Composition:** A specialized `draw_image` function allows for non-destructive composition of multiple source images onto a destination canvas.
- **Strict Memory Management:** Includes a full lifecycle management system (`load`, `save`, `destroy`) with zero memory leaks, even during partial allocation failures.
- **Pointer Arithmetic Core:** Per the project's high-performance constraints, all pixel access and array traversals are implemented using pointer arithmetic, bypassing the `[]` operator.



## 🧩 Key Functionalities
- **load_image_t / save_image_t:** Handles P2 (plain text) PGM headers, dimension parsing, and grayscale normalization (up to 255).
- **Pixel Accessors:** Provides `image_get_pixel` and `image_set_pixel` for safe, bounds-checked interaction with the raster data.
- **Coordinate-Based Drawing:** Supports multi-image merging with boundary validation to prevent memory corruption when drawing outside destination limits.

## 📊 Error Handling & Resilience
The engine is designed with a "fail-fast" and informative error reporting system:
- **Error Code 4:** File access issues.
- **Error Code 6:** Data corruption/Header mismatch validation.
- **Error Code 8:** Real-time heap allocation monitoring for high-resolution images.



## 📋 Demonstrated Skills
- **Advanced C Structures:** Nested dynamic allocation (pointer-to-pointer).
- **File I/O Engineering:** Manual parsing of structured text headers and bulk data streams.
- **Modular Programming:** Clean separation of concerns between `image_utils.h` (interface) and `image_utils.c` (implementation).

## 🚀 Usage Example
```bash
$ ./image_tool
Enter destination image file name: canvas.pgm
How many subimages you want to draw: 2
Enter a name of a subimage: logo.pgm
Enter coordinates (x, y): 100 150
File saved: canvas_modified.pgm