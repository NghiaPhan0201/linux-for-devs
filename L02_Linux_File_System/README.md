# Lab Session 2 Exercises

This repository contains C programs designed to practice file operations in operating systems, including opening files, reading/writing to files, and retrieving file information using `struct stat`. The three exercises are implemented in `excercise_1.c`, `excercise_2.c`, and `excercise_3.c`.

## Exercise 1: Using O_APPEND Flag and Seek

- **File:** `excercise_1.c`
- **Description:** This program opens a file named `testfile.txt` with the `O_APPEND` flag, attempts to seek to the beginning of the file using `lseek`, and then writes data. The goal is to observe where the data is written when the `O_APPEND` flag is used. The data will be written to the end of the file, regardless of whether you seek to the beginning or not, since the O_APPEND flag always ensures that the data is written to the end of the file.
- **Expected Outcome:** The data will be written to the **end of the file**, regardless of the seek to the beginning, because the `O_APPEND` flag always moves the file pointer to the end before writing.
- **How to Compile and Run:**
  1. Compile: `gcc -o excercise_1 excercise_1.c`
  2. Run: `./excercise_1`
  3. Check file content: `cat testfile.txt`
- **Note:** The file `testfile.txt` will be created if it does not already exist.

## Exercise 2: Read/Write File with Command-line Arguments

- **File:** `excercise_2.c`
- **Description:** This program accepts 4 command-line arguments: file name, number of bytes to read/write, mode (read `r` or write `w`), and content. Depending on the mode, it either reads from the file and prints to the screen or writes content to the file.
- **Syntax:** `./excercise_2 filename num-bytes [r/w] "content"`
  - `filename`: Name of the file.
  - `num-bytes`: Number of bytes to read/write.
  - `[r/w]`: Mode `r` for reading, `w` for writing.
  - `"content"`: Content to write (ignored if mode is read).
- **How to Compile and Run:**
  1. Compile: `gcc -o excercise_2 excercise_2.c`
  2. Example (write): `./excercise_2 testfile.txt 5 w "Hello"`
  3. Example (read): `./excercise_2 testfile.txt 5 r "Hello"`
- **Note:**
  - Ensure exactly 4 arguments are provided.
  - The file will be created if it does not exist during write mode.

## Exercise 3: Retrieve File Information with struct stat

- **File:** `excercise_3.c`
- **Description:** This program creates a file named `sample.txt`, writes sample data to it, and then uses `struct stat` to retrieve and display information: file name, file type, last modification time, and file size.
- **Expected Outcome:** The program prints to the screen:
  - File name.
  - File type (e.g., regular file, directory, symbolic link).
  - Last modification time.
  - File size (in bytes).
- **How to Compile and Run:**
  1. Compile: `gcc -o excercise_3 excercise_3.c`
  2. Run: `./excercise_3`
- **Note:** The file `sample.txt` will be created and populated with sample data.

## General Instructions

1. **Compilation:** Use the `gcc` commands as described for each exercise.
2. **Error Handling:** The programs use `perror` to report errors if issues occur during file opening, reading, writing, or retrieving information.
3. **Check Results:** Use the `cat` command to view file content or observe the terminal output.