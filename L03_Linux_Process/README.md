# Lab Session 3: Process Management in Linux

## Objectives

- Understand how to create and manage processes in Linux using C.
- Get familiar with `fork()`, `exec()`, `signal()`, `wait()`, and the concepts of zombie and orphan processes.

## Compilation and Execution

- Compile each program with: `gcc -o program_name file_name.c`
- Run the program: `./program_name`

## Exercise 1: Initialize and Track Process

- **Description**: Use `fork()` to create a child process. The child process prints its PID, and the parent process prints the child's PID.
- **File**: `excercise_1.c`
- **How to run**:

  ```bash
  gcc -o excercise_1 excercise_1.c
  ./excercise_1
  ```

- **Explanation**:
  - `fork()` creates a child process, returning 0 to the child and the child's PID to the parent.
  - `getpid()` retrieves the PID of the current process.

## Exercise 2: Using exec and Environment Variables

- **Description**: The child process replaces its running program with another, such as `ls` or `date`, based on the `COMMAND_TYPE` environment variable.
- **File**: `excercise_2.c`
- **How to run**:

  ```bash
  gcc -o excercise_2 excercise_2.c
  export COMMAND_TYPE=1
  ./excercise_2
  export COMMAND_TYPE=2
  ./excercise_2
  ```

- **Explanation**:
  - `execlp()` replaces the current process image with a new program (`ls` or `date`).
  - After `exec` is called, the original process code is completely replaced and does not return.
  - `getenv()` reads the `COMMAND_TYPE` environment variable to decide which command to execute.

## Exercise 3: Process Signals

- **Description**: The parent process sends a `SIGUSR1` signal to the child process after a delay, and the child handles and prints a message upon receiving it.
- **File**: `excercise_3.c`
- **How to run**:

  ```bash
  gcc -o excercise_3 excercise_3.c
  ./excercise_3
  ```

- **Explanation**:
  - `signal()` defines the behavior of the child when receiving the `SIGUSR1` signal.
  - `kill()` sends the signal from the parent to the child.
  - `pause()` makes the child wait for a signal.

## Exercise 4: Record Process Status

- **Description**: The parent process uses `wait()` to wait for the child to terminate and records its exit status.
- **File**: `excercise_4.c`
- **How to run**:

  ```bash
  gcc -o excercise_4 excercise_4.c
  ./excercise_4
  ```

- **Explanation**:
  - The child process calls `exit(42)` to terminate with exit code 42.
  - `wait()` allows the parent to wait for the child to finish.
  - `WIFEXITED()` checks if the child exited normally, and `WEXITSTATUS()` retrieves the exit code.

## Exercise 5: Create Zombie and Orphan Processes

- **Description**: Create a zombie process and an orphan process to understand these special process states, and observe them using `ps`.
- **Files**:
  - Zombie: `excercise_5_zombie.c`
  - Orphan: `excercise_5_orphan.c`
- **How to run**:

  ```bash
  gcc -o excercise_5_zombie excercise_5_zombie.c
  ./excercise_5_zombie &  # Run in background
  ps aux | grep excercise_5_zombie  # Observe zombie state
  ```

  ```bash
  gcc -o excercise_5_orphan excercise_5_orphan.c
  ./excercise_5_orphan &  # Run in background
  ps aux | grep excercise_5_orphan  # Observe orphan state
  ```

- **Explanation**:
  - **Zombie**: The child process completes, but the parent does not call `wait()` to clean it up, resulting in a zombie state ('Z' in `ps`). This happens because the system retains the child's status until the parent processes it.
  - **Orphan**: The parent process exits before the child, and the child is "adopted" by init (PID 1) or another system process, becoming an orphan.

## Notes

- Use `ps aux` to observe process states.
- Ensure compilation and execution are done on a Linux system.
- Be cautious with signals and sleep durations to avoid hanging processes.