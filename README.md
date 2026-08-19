# 🔐 Image Steganography using LSB in C

## 📌 Overview

This project implements **Image Steganography using the Least Significant Bit (LSB) technique** in C programming.

Steganography is the process of hiding secret information inside another file without making noticeable changes to the original file. In this project, a secret file is hidden inside a **BMP image** by modifying the Least Significant Bits of the image data.

The hidden data can later be extracted from the encoded image using the decoding process.

---

## 🎯 Objectives

- To understand the concept of Image Steganography
- To implement LSB-based data hiding
- To encode secret data into a BMP image
- To decode and extract the hidden data
- To understand file handling and binary data manipulation in C
- To implement a modular C programming project

---

## ⚙️ Working Principle

### 🔐 Encoding

The encoding process follows these steps:

1. Validate the command-line arguments.
2. Open the source BMP image and secret file.
3. Check whether the image has sufficient capacity.
4. Copy the BMP header.
5. Encode the magic string.
6. Encode the secret file extension size.
7. Encode the secret file extension.
8. Encode the secret file size.
9. Encode the secret file data.
10. Copy the remaining image data.
11. Generate the final stego image.

### 🔓 Decoding

The decoding process performs the reverse operation:

1. Open the encoded BMP image.
2. Decode and verify the magic string.
3. Decode the secret file extension size.
4. Decode the secret file extension.
5. Decode the secret file size.
6. Extract the hidden secret data.
7. Recreate the original secret file.

---

## 🧠 LSB Steganography

LSB stands for **Least Significant Bit**.

In this technique, the least significant bit of the image data is modified to store the secret information.

Example:

Original byte:

    10110100

Secret bit:

    00000001

Modified byte:

    10110101

Only the least significant bit is changed, so the visual difference in the image is very small.

---

## 🔑 Magic String

The project uses the following magic string to identify encoded images:

    avengers

During decoding, the magic string is extracted and compared with the predefined value to verify whether the image contains data encoded by this program.

---

## 📂 Project Structure

    .
    ├── main.c
    ├── encode.c
    ├── encode.h
    ├── decode.c
    ├── decode.h
    ├── header.h
    ├── enum.h
    ├── Tony.bmp
    ├── secret.txt
    ├── destination_encode.bmp
    └── vicky.txt

---

## 💻 Technologies & Concepts Used

- C Programming
- File Handling
- Pointers
- Structures
- Command Line Arguments
- Bitwise Operators
- LSB Bit Manipulation
- Dynamic Memory Allocation
- BMP File Handling
- Binary File Operations
- Modular Programming

---

## 🚀 Compilation

Compile the project using GCC:

    gcc main.c encode.c decode.c -o steganography

---

## ▶️ Usage

### Encoding

    ./steganography -e source.bmp secret.txt

Example:

    ./steganography -e Tony.bmp secret.txt

The encoded image will be generated as:

    destination_encode.bmp

### Decoding

    ./steganography -d destination_encode.bmp

The hidden secret file will be extracted from the encoded image.

---

## 🔄 Project Flow

    Source BMP Image
            |
            v
       LSB Encoding
            |
            +-------------------+
            |                   |
            v                   v
      Magic String        Secret File
                              |
                              v
                       File Extension
                              |
                              v
                         File Size
                              |
                              v
                       Secret Data
            |
            v
      Stego BMP Image
            |
            v
       LSB Decoding
            |
            v
      Secret File Extracted

---

## ✅ Features

- BMP image-based steganography
- LSB-based data hiding
- Secret file encoding and decoding
- Secret file extension preservation
- Secret file size encoding
- Magic string verification
- Command-line interface
- Modular C implementation

---

## ⚠️ Limitations

- Currently supports BMP images.
- The source image must have sufficient capacity to store the secret data.
- This project demonstrates the fundamentals of steganography and is intended primarily for educational purposes.

---

## 📚 Learning Outcomes

Through this project, I gained practical experience in:

- Binary file manipulation
- BMP image handling
- Bit-level programming
- Pointers and structures
- File pointer operations
- Command-line arguments
- Encoding and decoding algorithms
- Modular programming in C

---

## 👨‍💻 Author

**Vicky**

### Project: Image Steganography using LSB in C
