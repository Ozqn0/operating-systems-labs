# Example 03 – Using lseek() to Move the File Offset and Read Data

## Purpose

This example demonstrates how to reposition the file offset of an open file using lseek(), then read data from that new position and write it to standard output. It shows the use of low-level POSIX file operations to seek, read, and write, and how to handle basic error conditions.

## System Calls / Functions Used

- open(2) (fcntl.h) — open a file and obtain a file descriptor.
- lseek(2) (unistd.h) — reposition the file offset for a file descriptor.
- read(2) (unistd.h) — read raw bytes from a file descriptor.
- write(2) (unistd.h) — write raw bytes to a file descriptor (here STDOUT_FILENO).
- close(2) (unistd.h) — close a file descriptor when finished.
- perror (stdio.h) — print an error message describing the last error (uses errno).
- exit (stdlib.h) — terminate the program with a status code.
- Types and headers:
  - #include <unistd.h>
  - #include <fcntl.h>
  - #include <sys/types.h>
  - #include <sys/stat.h>
  - #include <stdio.h>
  - #include <stdlib.h>

## How It Works

1. The program attempts to open a file named "seeking" with `open("seeking", O_RDWR)`. The returned file descriptor is stored in `f`.
2. If `open()` fails (returns -1), the program calls `perror()` with a message and exits with status 1.
3. `lseek(f, 10, SEEK_SET)` moves the file offset to byte position 10 from the start of the file. The new offset is stored in `f1` (type off_t).
4. If `lseek()` returns `(off_t)-1`, an error occurred; the program prints an error message, closes the file descriptor, and exits.
5. The program prints the current offset value to the console.
6. `read(f, buff, 10)` attempts to read up to 10 bytes from the file starting at the new offset. The number of bytes actually read is stored in `n`.
7. If `read()` returns a negative value, an error occurred; the program prints an error message, closes the file, and exits.
8. `write(STDOUT_FILENO, buff, n)` writes the bytes that were read to standard output (echoing them).
9. The program writes a newline, closes the file descriptor with `close(f)`, and exits with status 0.

Practical effect:
- The program reads 10 bytes starting at offset 10 of the file "seeking" and prints them to stdout. It also prints the numerical position returned by lseek().

## Important Notes and Recommended Improvements

- File open flags: The code uses `O_RDWR` to open the file for reading and writing. If the program only needs to read, prefer `O_RDONLY`.
- Return types: Use `ssize_t` for `read()`/`write()` return variables (instead of `int`) because they can return -1 on error and their type is signed.
- Printing off_t: The program casts `f1` to `long` for printing. For portability, consider casting to `long long` and using `printf("%lld", (long long)f1)` or include <inttypes.h> and use `printf("%jd", (intmax_t)f1)`.
- Error messages language: The current code calls `perror()` with Turkish messages ("Dosya açma hatası", "Lseek hatası", "Okuma hatası"). Repository rules require English documentation and comments; it is recommended to use English messages (for example, "open error", "lseek error", "read error") so output is consistent for all students.
- EOF handling: If `read()` returns 0, the program reached EOF. The code should handle this case explicitly if needed.
- Resource management: The example correctly closes the file descriptor on normal and some error paths; ensure all error paths close any opened descriptor to avoid leaks.
- Robustness: Always check return values for `open`, `lseek`, `read`, and `write`. Consider looping on partial reads/writes if you intend to transfer larger amounts of data.
- Permissions and file existence: If "seeking" does not exist, `open()` will fail. For testing, create the file first (see How to Run).

## How to Compile and Run

Compile:
$ gcc main.c -o app

Run (example steps):
1. Prepare a sample file:
$ printf "0123456789ABCDEFGHIJ" > seeking
(This creates a file whose bytes at offsets 0..19 are the digits and letters; bytes 10..19 are "ABCDEFGHIJ".)
2. Run the program:
$ ./app

Expected output:
- A line showing the pointer position (e.g., "Pointer is now 10.") — exact message depends on the program's printf format.
- The 10 bytes read starting at offset 10 printed to stdout (e.g., "ABCDEFGHIJ"), followed by a newline.



