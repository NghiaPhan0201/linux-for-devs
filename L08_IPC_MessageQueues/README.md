# POSIX Message Queue Exercises

This project contains three C programs demonstrating the use of POSIX message queues for inter-process communication.

## Requirements

- A POSIX-compliant system (e.g., Linux)
- GCC compiler
- The `librt` library for POSIX message queue support

## Programs

### bt1: Simple Message Sending and Receiving

- Creates a message queue using `mq_open()`.
- The parent process sends a simple string message to the child process.
- The child process receives and prints the message.
- The queue is closed and unlinked after use.

### bt2: Character Counting via Message Queue

- Creates two message queues: one for sending a string and one for receiving the count.
- The parent process sends a string to the child process.
- The child process counts the characters in the string and sends the count back.
- The parent process receives and prints the count.
- Both queues are closed and unlinked after use.

### bt3: Communication Between Multiple Processes

- Creates a message queue for communication between three processes.
- The parent process sends a string to the queue.
- Child process 1 receives the string, converts it to uppercase, and sends it back to the queue.
- Child process 2 receives the modified string and prints it.
- The queue is closed and unlinked after use.

## Build Instructions

1. Ensure you have GCC and `librt` installed.
2. Run the following commands:

   ```bash
   make
   ```

3. This will compile all three programs: `bt1`, `bt2`, and `bt3`.

## Run Instructions

- Execute each program individually:

  ```bash
  ./bt1
  ./bt2
  ./bt3
  ```

## Clean Up

- Remove compiled binaries:

  ```bash
  make clean
  ```

## Notes

- Ensure proper permissions for message queues (mode 0644 is used).
- Error handling is included for queue operations and process creation.
- The programs use a maximum message size of 1024 bytes and a queue capacity of 10 messages.
