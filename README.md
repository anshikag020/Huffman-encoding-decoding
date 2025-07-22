# Huffman Compression-Decompression Tool

**Author:** Anshika Gupta  
**Course Roll No:** CS22BTECH11007  

## Description
This project implements **file compression and decompression** using **Huffman Encoding**. It provides an interactive command-line tool to compress and decompress files efficiently.

Example compressed and decompressed files are included:
- `compress.txt` (compressed output example, ~4.07 KB)
- `decompress.txt` (decompressed output example, ~6.79 KB)

---

## How to Compile
Compile all the `.cpp` files together using g++:

```bash
g++ main.cpp compress.cpp decompress.cpp -o huffman_tool
```

This will create an executable named `huffman_tool`.

---

## How to Run
Run the executable:

```bash
./huffman_tool
```

You will be prompted:

```
Do you wish to compress, decompress or exit?:
```

### Options:
- **compress:** Compress a file.
- **decompress:** Decompress a previously compressed file.
- **exit:** Exit the tool.

---

## Usage

### Compression
1. Type `compress` when prompted.
2. Enter the **path to the file to compress**.
3. Enter the **name for the compressed output file**.

### Decompression
1. Type `decompress` when prompted.
2. Enter the **path of the compressed file**.
3. Enter the **name for the decompressed output file**.

---

## File Structure

| File             | Description                           |
|------------------|---------------------------------------|
| `main.cpp`       | Provides the interactive CLI for compressing/decompressing files. |
| `compress.cpp`   | Contains the Huffman Encoding logic for compression. |
| `decompress.cpp` | Contains the logic for decoding/compression reversal. |
| `Huffman_node.h` | Defines the **Node** structure for Huffman Tree and constants used for encoding. |
| `compress.txt`   | Example of a compressed file output (~4.07 KB). |
| `decompress.txt` | Example of the decompressed file output (~6.79 KB). |

---

## Special Constants in `Huffman_node.h`
- `PSEUDO_EOF`: Marks the end of encoded data.
- `CHAR_CODE_SEPARATOR`: (Not actively used in current implementation).
- `CODES_SEPARATOR`: Separates codes in the header.
- `CODE_TEXT_SEPARATOR`: Marks the end of the header and start of encoded data.

---

## Example Run

### Compressing a file:
```
Do you wish to compress, decompress or exit?: compress
Enter path to the file to be compressed: sample.txt
Enter name of output file: compressed.huff
```

### Decompressing a file:
```
Do you wish to compress, decompress or exit?: decompress
Enter path to the file to be decompressed: compressed.huff
Enter name of decompressed file: output.txt
```

### Exiting:
```
Do you wish to compress, decompress or exit?: exit
```

---

## Requirements
- C++ compiler (e.g., g++)
- Compatible with Unix/Linux systems like **Ubuntu 22.04 LTS**

---
```
