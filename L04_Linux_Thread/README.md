# Thread Programming Exercises with Pthreads

This repository contains six exercises demonstrating the use of the `pthread.h` library in C for multi-threading, synchronization, and resource sharing.

## Prerequisites

- **Compiler**: GCC (GNU Compiler Collection)
- **Library**: `pthread.h` (POSIX threads)
- **OS**: Linux/Unix-based system
- Compile each program with: `gcc -o <program_name> <file_name>.c -pthread`
- Run with: `./<program_name>`

## Exercises

### Exercise 1: Basic Thread Creation and Execution

- **Objective**: Create two threads, each printing a message with its thread ID, and wait for them to complete using `pthread_join`.
- **Key Concepts**:
  - `pthread_create`: Creates a new thread.
  - `pthread_join`: Waits for threads to finish.
  - Threads end when their routine function completes.
- **File**: `exercise_1.c`
- **Run**: `gcc -o exercise_1 exercise_1.c -pthread && ./exercise_1`
- **Output**: Displays "Thread 1: Hello from thread" and "Thread 2: Hello from thread", followed by a completion message.

### Exercise 2: Thread Synchronization with Mutex

- **Objective**: Create three threads, each incrementing a global `counter` 1,000,000 times, using a mutex for safe access.
- **Key Concepts**:
  - **Why mutex?** Prevents race conditions when multiple threads modify `counter` simultaneously.
  - **Without mutex**: The final value may be incorrect (less than 3,000,000) due to overlapping updates.
  - Uses `pthread_mutex_lock` and `pthread_mutex_unlock` for synchronization.
- **File**: `exercise_2.c`
- **Run**: `gcc -o exercise_2 exercise_2.c -pthread && ./exercise_2`
- **Output**: Shows the final value of `counter` (should be close to 3,000,000).

### Exercise 3: Using Condition Variables

- **Objective**: Implement a producer-consumer model with two threads: producer generates random numbers (1-10), consumer reads and prints them, synchronized with condition variables.
- **Key Concepts**:
  - `pthread_cond_wait`: Consumer waits for producer to signal data is ready.
  - `pthread_cond_signal`: Producer notifies consumer after generating data.
  - Repeats 10 times.
- **File**: `exercise_3.c`
- **Run**: `gcc -o exercise_3 exercise_3.c -pthread && ./exercise_3`
- **Output**: Displays generated numbers and consumer reads, 10 iterations.

### Exercise 4: Counting Even and Odd Numbers with Threads

- **Objective**: Generate a random array of 100 integers (1-100), use two threads to count even and odd numbers, and print the results.
- **Key Concepts**:
  - No mutex needed as threads work on separate tasks (counting even vs. odd).
  - Uses `pthread_join` to ensure completion before printing.
- **File**: `exercise_4.c`
- **Run**: `gcc -o exercise_4 exercise_4.c -pthread && ./exercise_4`
- **Output**: Shows the total count of even and odd numbers.

### Exercise 5: Resource Sharing with Read-Write Lock

- **Objective**: Simulate resource sharing with 5 reader threads and 2 writer threads operating on a shared `data` variable, using a read-write lock.
- **Key Concepts**:
  - `pthread_rwlock_rdlock`: Allows multiple readers to access `data` simultaneously.
  - `pthread_rwlock_wrlock`: Ensures only one writer modifies `data` at a time.
- **File**: `exercise_5.c`
- **Run**: `gcc -o exercise_5 exercise_5.c -pthread && ./exercise_5`
- **Output**: Shows reader and writer actions, final value of `data`.

### Exercise 6: Array Sum with Threads and Mutex

- **Objective**: Compute the sum of a 1,000,000-element array by dividing it into 4 parts, with 4 threads summing each part, using a mutex to update a global sum.
- **Key Concepts**:
  - Mutex protects the global `total_sum` from concurrent updates.
  - Each thread processes a quarter of the array.
- **File**: `exercise_6.c`
- **Run**: `gcc -o exercise_6 exercise_6.c -pthread && ./exercise_6`
- **Output**: Displays the total sum of the array.

## Notes

- **Compilation**: Use `-pthread` flag to link the pthread library.
- **Behavior**: Output may vary due to thread scheduling or random values.
- **Cleanup**: Mutexes, condition variables, and read-write locks are properly initialized and destroyed to avoid resource leaks.