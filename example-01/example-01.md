# Example 01 – Using read() and write() system calls

## Purpose

This small example demonstrates basic use of low-level I/O system calls in C: write() to send data to a file descriptor (stdout) and read() to receive data from a file descriptor (stdin). The program prints a fixed message, shows the return value of write(), then reads up to 30 bytes from standard input and echoes those bytes back to standard output.

## System Calls / Functions Used

- write(2) (unistd.h) — writes raw bytes to a file descriptor. Here it is used to send data to stdout (file descriptor 1).
- read(2) (unistd.h) — reads raw bytes from a file descriptor. Here it is used to read from stdin (file descriptor 0).
- printf (stdio.h) — formatted output to stdout (used to print the return value of write()).
- main — program entry point.
- Custom helper functions: write_fonksiyonu and read_fonksiyonu (wrapper functions that call write/read).

Headers included in the source:
- #include <unistd.h>
- #include <stdio.h>

## How It Works

1. The program declares two local integers in main: `n` and `m`. (They are not initialized before use — see the "Important notes" section below.)
2. `write_fonksiyonu(n)` is called:
   - Inside `write_fonksiyonu`, the call `write(1, "Hello", 5)` writes the 5 bytes of the string "Hello" to stdout.
   - The return value of write (number of bytes written, or -1 on error) is stored in the local parameter `m`.
   - `printf` prints the value stored in `m` (typically `5` on success).
3. `read_fonksiyonu(m)` is called:
   - Inside `read_fonksiyonu`, a local buffer `char b[30]` is declared.
   - `read(0, b, 30)` attempts to read up to 30 bytes from stdin into `b`. The number of bytes actually read is stored in the local parameter `n`.
   - `write(1, b, n)` writes the bytes that were read back to stdout (echo behavior).
4. Program returns 0 and exits.

Important notes and recommended fixes:
- Undefined behavior: In the current code `n` and `m` are uninitialized local variables in main and are passed by value to the functions. Passing an uninitialized variable as an argument reads its indeterminate value and thus causes undefined behavior in C. Although the functions immediately overwrite their parameters with the return values of read/write, the act of passing an uninitialized automatic variable is undefined.
- Two safe alternatives:
  - Initialize the variables in main before passing them (e.g., `int n = 0, m = 0;`), or
  - Change the helper functions so they do not accept these integer parameters (since they are unused on function entry) or return the values instead. Example signatures:
    - `int write_fonksiyonu(void)` and `int read_fonksiyonu(void)`, or
    - `int write_fonksiyonu(void) { return write(1, "Hello", 5); }` and capture the return in main.
  - Another option: pass pointers to receive the values (e.g., `int read_fonksiyonu(int *out_n)`).
- Error handling: The example does not check for errors from read/write (which return -1 on error). In production or lab code, always check return values and handle errors.

## How to Compile and Run

Compile:
$ gcc main.c -o app

Run:
$ ./app

Expected runtime behavior:
- The program prints "Hello" followed by a line indicating the number of bytes written (usually `value of n is 5`).
- The program then waits for input from stdin. Type up to 30 characters and press Enter; the program echoes back the bytes you typed.



