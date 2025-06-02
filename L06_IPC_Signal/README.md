# Signal Handling Practice in C

This repository contains five C programs for practicing signal handling in Linux/Unix-like systems. Each program demonstrates a different aspect of signal handling, such as catching signals, creating timers, inter-process communication, ignoring signals, and combining signal handling with user input.

## Requirements

- **Compiler**: GCC (GNU Compiler Collection)
- **Operating System**: Linux, macOS, or Windows (with MinGW or WSL)

## Programs

### 1. exercise_1: Catching SIGINT Signal

- **File**: `exercise_1.c`
- **Description**: A program that catches the SIGINT signal (sent by pressing Ctrl+C) and prints "SIGINT received". It exits after receiving SIGINT 3 times.
- **Compile**:

  ```bash
  gcc -o exercise_1 exercise_1.c
  ```

- **Run**:

  ```bash
  ./exercise_1
  ```

- **Test**: Press `Ctrl+C` to send SIGINT. The program exits after 3 signals.

### 2. exercise_2: Timer Using SIGALRM

- **File**: `exercise_2.c`
- **Description**: A program that uses the SIGALRM signal to create a timer. It increments a counter every second and prints "Timer: `seconds` seconds". The program exits after 10 seconds.
- **Compile**:

  ```bash
  gcc -o exercise_2 exercise_2.c
  ```

- **Run**:

  ```bash
  ./exercise_2
  ```

- **Test**: Watch the timer count up to 10 seconds and exit.

### 3. exercise_3: Inter-Process Communication Using SIGUSR1

- **File**: `exercise_3.c`
- **Description**: A program that creates a parent and child process using `fork()`. The parent sends the SIGUSR1 signal to the child every 2 seconds, and the child prints "Received signal from parent". The program stops after 5 signals.
- **Compile**:

  ```bash
  gcc -o exercise_3 exercise_3.c
  ```

- **Run**:

  ```bash
  ./exercise_3
  ```

- **Test**: Observe the parent sending signals and the child responding.

### 4. exercise_4: Ignoring SIGTSTP Signal

- **File**: `exercise_4.c`
- **Description**: A program that catches and ignores the SIGTSTP signal (sent by Ctrl+Z). Instead of stopping, it prints "SIGTSTP ignored" and continues running.
- **Compile**:

  ```bash
  gcc -o exercise_4 exercise_4.c
  ```

- **Run**:

  ```bash
  ./exercise_4
  ```

- **Test**: Press `Ctrl+Z` to send SIGTSTP. The program will ignore it and keep running.

### 5. exercise_5: Signal Handling with User Input

- **File**: `exercise_5.c`
- **Description**: A program that handles SIGINT and SIGTERM signals while allowing user input from the keyboard. It uses `select()` to wait for input without blocking signal handling. Prints "SIGINT received" for SIGINT and exits on SIGTERM.
- **Compile**:

  ```bash
  gcc -o exercise_5 exercise_5.c
  ```

- **Run**:

  ```bash
  ./exercise_5
  ```

- **Test**:
  - Press `Ctrl+C` to send SIGINT and see "SIGINT received."
  - In another terminal, find the PID with `ps` and send SIGTERM: `kill -TERM <pid>`
  - Type text to see your input echoed back.

## Notes

- Use `ps` or `top` to find the PID of a running program if needed.
- To send SIGTERM manually, use: `kill -TERM <pid>`
- These programs are designed for Unix-like systems and may not work as expected on Windows without adjustments.
