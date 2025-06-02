# Pipe Communication in C

This repository contains three C programs demonstrating the use of pipes for inter-process communication (IPC) between parent and child processes.

## Programs

### 1. BT1: Basic Pipe Communication

- **Description**: A simple program that uses a pipe for communication between a parent and a child process.
- **Functionality**:
  - The parent process sends a string ("Hello from parent") to the child via a pipe.
  - The child process reads the string from the pipe and prints it to the console.
- **Key Functions**: `pipe()`, `fork()`, `write()`, `read()`

### 2. BT2: Multiple Pipes for Multiple Processes

- **Description**: An extended program using two pipes for communication across three processes.
- **Functionality**:
  - The parent process sends a message ("Hello from parent") to child 1 via the first pipe.
  - Child 1 receives the message, appends " - modified by child 1", and sends it to child 2 via the second pipe.
  - Child 2 receives the modified message and prints it to the console.
- **Key Functions**: `pipe()`, `fork()`, `write()`, `read()`, `strcat()`

### 3. BT3: Character Counting via Pipe

- **Description**: A program that uses a pipe to send a string and count its characters.
- **Functionality**:
  - The parent process sends a string ("Hello, this is a test string") to the child via a pipe.
  - The child process reads the string, counts its characters, and prints both the string and the character count.
- **Key Functions**: `pipe()`, `fork()`, `write()`, `read()`, `strlen()`

## How to Compile and Run

1. Clone this repository to your local machine.
2. Navigate to the project directory.
3. Compile each program using the following command:

   ```bash
   gcc -o bt1 bt1.c
   gcc -o bt2 bt2.c
   gcc -o bt3 bt3.c
   ```

4. Run the compiled programs:

   ```bash
   ./bt1
   ./bt2
   ./bt3
   ```

## Notes

- Ensure proper closure of unused pipe ends to avoid deadlocks.
- The programs are designed for Unix-like systems where `fork()` and `pipe()` are supported.
