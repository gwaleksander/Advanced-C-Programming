# LSB Image Steganography

A low-level C implementation of the **Least Significant Bit (LSB)** steganography technique. The tool allows hiding and extracting text messages within monochromatic image data without visible loss of image quality.

## 🛠 Technical Highlights
- **Bitwise Manipulation:** Direct access to the last bit of each pixel byte to store message bits.
- **Unions for Data Access:** Utilizing C `unions` to map between raw bytes and bit-fields, ensuring efficient and readable bit-level access.
- **Pointer-Only Architecture:** In compliance with strict engineering constraints, the entire project avoids the `[]` operator, relying solely on pointer arithmetic.
- **Binary Stream Processing:** Handles monochromatic image formats where each byte represents a pixel brightness level (0-255).



## 🧩 Key Features
- **Encoding Mode:** Embeds a text message into a source image file and saves it as a new steganographic carrier.
- **Decoding Mode:** Scans a modified image file to reconstruct the hidden message by harvesting the least significant bits of consecutive pixels.
- **Error Handling:** Robust validation for file access, I/O errors, and data corruption.

## 🧠 Engineering Concept: Why LSB?
In a monochromatic image, changing the value of a pixel by 1 (e.g., from 128 to 129) is imperceptible to the human eye. By replacing the 8th bit of 8 consecutive pixels, we can hide 1 full byte of secret data. 



## 📊 Demonstrated Skills
- **Low-Level Data Mapping:** Using unions to bridge the gap between high-level logic and binary representation.
- **Manual Memory Offsets:** Navigating image buffers using pointers to maintain high performance.
- **Information Security:** Practical application of data hiding techniques and binary file integrity checks.

## 🚀 Usage Example
```bash
# To encode a message:
$ ./stegano
Do you want to encode (E/e) or decode (D/d) a message? E
Enter a message: "Hidden message"
Enter input file name: image.txt
Enter output file name: secret_image.txt
File saved!

# To decode:
$ ./stegano
Do you want to encode (E/e) or decode (D/d) a message? D
Enter input file name: secret_image.txt
# Output: Hidden message