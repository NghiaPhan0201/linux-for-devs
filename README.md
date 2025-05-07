# linux-for-devs

## L01_General_Knowledge

Main contents of this lesson:
1. **Makefile**
2. **The Process of Compiling C Program**
3. **Static Library & Shared Library**

### 1. **Makefile**

A **Makefile** is a script used with the `make` utility to automate the compilation and building of programs. It defines rules, dependencies, and commands to compile source code, link libraries, and generate executables. By using a Makefile, developers can streamline repetitive tasks, ensure consistent builds, and manage complex projects efficiently.

- **Key Components**:
  - **Targets**: Goals to achieve, such as generating an executable or library (e.g., `all`, `clean`).
  - **Dependencies**: Files required to build a target (e.g., source files or object files).
  - **Commands**: Shell commands to execute, like `gcc` for compilation or `rm` for cleanup.
  - **Variables**: Store reusable values, such as `CC=gcc` for the compiler or `CFLAGS=-Wall` for compiler flags.

- **Example**:
  ```makefile
  all: create_obj create_static
  create_obj: calc/*.c
      mkdir -p obj
      gcc -Wall -c calc/*.c -o obj/
  create_static: create_obj
      mkdir -p lib
      ar rcs lib/libcalc.a obj/*.o
  clean:
      rm -rf obj lib
  ```
  This Makefile compiles C source files, creates a static library, and cleans up generated files.

- **Why Use It?**: Saves time, reduces errors, and simplifies managing large projects with multiple files.

### 2. **The Process of Compiling C Program**

Compiling a C program involves transforming human-readable source code (`.c` files) into machine-executable code. This process typically consists of four stages:

- **Preprocessing**:
  - The preprocessor handles directives like `#include` and `#define`.
  - It expands macros, includes header files, and produces a temporary file.
  - Example command: `gcc -E source.c -o source.i`

- **Compilation**:
  - The compiler translates the preprocessed code into assembly code.
  - It checks syntax and generates assembly instructions.
  - Example command: `gcc -S source.i -o source.s`

- **Assembly**:
  - The assembler converts assembly code into machine code, producing object files (`.o`).
  - These files contain binary instructions but are not yet executable.
  - Example command: `gcc -c source.s -o source.o`

- **Linking**:
  - The linker combines object files, resolves references to libraries, and produces the final executable.
  - It ensures all functions and symbols are correctly connected.
  - Example command: `gcc source.o -o program`

- **Why It Matters**: Understanding these stages helps developers debug errors, optimize code, and work with build tools like `make`.

### 3. **Static Library & Shared Library**

Libraries in C allow code reuse by bundling functions into reusable modules. There are two types: **static libraries** and **shared libraries**.

- **Static Library (`.a`)**:
  - A collection of object files (`.o`) archived together, linked directly into the executable during compilation.
  - **Creation**: Use `ar rcs` to create (e.g., `ar rcs libcalc.a obj/*.o`).
  - **Usage**: Linked with `-l` and `-L` flags (e.g., `gcc main.c -Llib -lcalc -o program`).
  - **Pros**: Self-contained executable, faster execution (no runtime loading).
  - **Cons**: Larger executable size, updates to the library require recompilation.

- **Shared Library (`.so`)**:
  - A dynamically linked library loaded at runtime, shared across multiple programs.
  - **Creation**: Use `gcc -shared` (e.g., `gcc -shared -o libcalc.so obj/*.o`).
  - **Usage**: Linked with `-l` and `-L`, requires `LD_LIBRARY_PATH` to locate the library (e.g., `LD_LIBRARY_PATH=lib ./program`).
  - **Pros**: Smaller executable size, easier to update (no recompilation needed).
  - **Cons**: Slower startup (due to runtime loading), dependency on library availability.

- **Example**:
  - Static: `gcc main.c -Icalc -Llib -lcalc -o test_static` (links `libcalc.a`).
  - Shared: `gcc main.c -Icalc -Llib -lcalc -o test_shared` and `LD_LIBRARY_PATH=lib ./test_shared` (uses `libcalc.so`).

- **Why It Matters**: Libraries promote modularity, reduce code duplication, and optimize resource usage in software development.


## L02_Linux_File_System

## L03_Linux_Process

## L04_Linux_Thread

## L05_IPC_Socket

## L06_IPC_Signal

## L07_IPC_Pipes
