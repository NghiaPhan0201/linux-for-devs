# Static and Shared Library Project

## Introduction

This project demonstrates how to create two types of libraries in C:
1. **Static Library** (`libcalc.a`)
2. **Shared Library** (`libcalc.so`)

We use a Makefile to automate the compilation, linking, and library creation process. The goal is to provide an example of how to build and use both static and shared libraries in C, while helping users understand the build process using Makefile.

## Project Structure

```
.
├── p01_static_lib
│   ├── calc
│   │   ├── calc_add.c
│   │   ├── calc_div.c
│   │   ├── calc.h
│   │   ├── calc_mul.c
│   │   └── calc_sub.c
│   ├── main.c
│   └── Makefile
├── p02_shared_lib
│   ├── calc
│   │   ├── calc_add.c
│   │   ├── calc_div.c
│   │   ├── calc.h
│   │   ├── calc_mul.c
│   │   └── calc_sub.c
│   ├── main.c
│   └── Makefile
└── README.md
```

- **p01_static_lib**: Contains source code for the static library (`libcalc.a`).
- **p02_shared_lib**: Contains source code for the shared library (`libcalc.so`).
- **README.md**: Documentation explaining the project structure and build process.
- **calc**: Each subdirectory (`p01_static_lib/calc`, `p02_shared_lib/calc`) holds the source files for basic arithmetic operations: add, subtract, multiply, divide.
- **main.c**: A sample program to test the static or shared library.
- **Makefile**: Automates the compilation and build process.

## Compilation and Linking with Makefile

Below is a detailed explanation of the main parts of the Makefile used in each folder (`p01_static_lib` and `p02_shared_lib`).

### 1. **Makefile Variables**

#### `CC` – C Compiler
- Specifies the C compiler. Default is `gcc`.

#### `AR` – Archiver Tool for Static Libraries
- Used to create static libraries in `p01_static_lib`. The `ar rcs` command creates a static library from object files.

#### `CFLAGS` – Compiler Flags
- Compiler options. For example: `-Wall` enables all warnings, and `-fPIC` (used in `p02_shared_lib`) ensures position-independent code for shared libraries.

#### `LDFLAGS` – Linker Flags
- Linker options. For example: `-shared` (used in `p02_shared_lib`) creates a shared library.

### 2. **Makefile Targets**

#### `all` – Default Target
- The default target when running `make`. It triggers the creation of the library.
  - In `p01_static_lib`, it builds the static library (`lib/libcalc.a`).
  - In `p02_shared_lib`, it builds the shared library (`lib/libcalc.so`).

#### `create_static` – Static Library Build Target (only in `p01_static_lib`)
- Creates the static library from object files.
  - Uses the command: `ar rcs lib/libcalc.a obj/*.o`.
  - Ensures the `lib` directory exists using `mkdir -p lib`.

#### `create_shared` – Shared Library Build Target (only in `p02_shared_lib`)
- Creates the shared library from object files.
  - Uses the command: `gcc -shared -o lib/libcalc.so obj/*.o`.
  - Ensures the `lib` directory exists using `mkdir -p lib`.

#### `create_obj` – Compile Source Files
- Compiles all `.c` source files in the `calc` directory into corresponding `.o` object files in the `obj` directory.
  - In `p01_static_lib`, uses `gcc -Wall -c calc/*.c -o obj/`.
  - In `p02_shared_lib`, uses `gcc -Wall -fPIC -c calc/*.c -o obj/` to ensure compatibility with shared libraries.
  - Ensures the `obj` directory exists using `mkdir -p obj`.

#### `run` – Run the Sample Program
- Compiles and runs the test program (`main.c`) using the created library.
  - In `p01_static_lib`, links with the static library using `gcc main.c -Icalc -Llib -lcalc -o test_static` and runs `./test_static`.
  - In `p02_shared_lib`, links with the shared library using `gcc main.c -Icalc -Llib -lcalc -o test_shared` and runs `LD_LIBRARY_PATH=lib ./test_shared` to ensure the shared library is found.

#### `clean` – Remove Temporary Files
- Deletes the `obj` and `lib` directories and any generated test executables (`test_static` in `p01_static_lib`, `test_shared` in `p02_shared_lib`).
  - Uses the command: `rm -rf obj lib test_static` or `rm -rf obj lib test_shared`.

### 3. **Usage Instructions**

#### Build and Run Static Library

To compile and run the static library, run the following commands inside the `p01_static_lib` directory:

```bash
cd p01_static_lib
make run
```

This will:
- Compile source files in `calc/` into object files in `obj/`.
- Create the static library `lib/libcalc.a`.
- Compile and run the `main.c` program with the static library, producing `test_static`.

#### Build and Run Shared Library

To compile and run the shared library, run the following commands inside the `p02_shared_lib` directory:

```bash
cd p02_shared_lib
make run
```

This will:
- Compile source files in `calc/` into object files in `obj/` with `-fPIC`.
- Create the shared library `lib/libcalc.so`.
- Compile and run the `main.c` program with the shared library, producing `test_shared`.

#### Clean the Project

To remove all generated files and directories, run:

```bash
make clean
```

This command deletes the `obj`, `lib` directories, and test executables (`test_static` or `test_shared`).


## Conclusion

This project helps you understand how to create and use static and shared libraries in C. By using Makefile, you can automate the build process, generate libraries, and run test programs efficiently.