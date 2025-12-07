# Example 02 – Copying Bytes Between Files Using open(), read(), and write()

## Purpose

This example demonstrates basic file I/O at the POSIX level in C. The program opens a source file ("text.txt") for reading, reads a small number of bytes into a buffer, prints how many bytes were read, then opens (or creates) a target file ("target") and writes the bytes that were read into that file.

## System Calls / Functions Used

- open(2) (fcntl.h) — open a file descriptor for reading or writing.
- read(2) (unistd.h) — read raw bytes from a file descriptor.
- write(2) (unistd.h) — write raw bytes to a file descriptor.
- printf (stdio.h) — formatted output to stdout.
- close(2) (unistd.h) — (recommended) close file descriptors when done.
- Types and headers used:
  - #include <unistd.h>
  - #include <fcntl.h>
  - #include <sys/types.h>
  - #include <sys/stat.h>
  - #include <stdio.h>

## How It Works

1. The program declares `int n, fd, fd1;` and `char buffer[50];`.
2. `open("text.txt", O_RDONLY)` opens the file named "text.txt" for reading and returns a file descriptor stored in `fd`.
3. `read(fd, buffer, 10)` reads up to 10 bytes from `fd` into `buffer` and stores the number of bytes actually read in `n`.
4. `printf("Number of bytes read: %d\n", n);` prints how many bytes were read. If `read` returns -1, an error occurred.
5. `open("target", O_CREAT | O_WRONLY, 0642)` opens (or creates) a file named "target" for writing and returns a file descriptor stored in `fd1`. The given mode 0642 sets owner/group/other permissions for the newly created file (subject to the process umask).
6. `write(fd1, buffer, n)` writes `n` bytes from `buffer` into the target file.
7. The program returns 0 and exits.

Important behavior details:
- The program reads only the first 10 bytes from "text.txt" even though `buffer` can hold 50 bytes.
- The program currently does not close file descriptors after use.
- The program does not verify return values from `open`, `read`, or `write`, so errors are not handled.

## Recommended Improvements and Notes

- Always check return values:
  - Verify `open()` did not return -1 before using the descriptor.
  - Verify `read()` and `write()` return non-negative values and handle -1 (errno) properly.
- Use appropriate types for byte counts: `ssize_t` is the correct return type for `read()`/`write()`.
- Close file descriptors with `close(fd)` and `close(fd1)` when finished to avoid resource leaks.
- Consider reading up to `sizeof(buffer)` (e.g., `read(fd, buffer, sizeof(buffer))`) instead of a hard-coded `10` if you intend to use the full buffer.
- Use an appropriate file creation mode (e.g., `0644`) unless `0642` is intentional. Remember the process umask may further restrict permissions.
- Add error messages (e.g., using `perror()` or printing `strerror(errno)`) to help debugging.

## How to Compile and Run

Compile:
$ gcc main.c -o app

Run (example):
1. Create a source file:
$ echo "Hello, Operating Systems!" > text.txt
2. Run the program:
$ ./app
3. Inspect the result:
$ cat target

Expected behavior on success:
- The program prints the number of bytes it read (e.g., "Number of bytes read: 10").
- The first `n` bytes from text.txt are written into the file named "target".

## Example of safer code changes (summary)

- Initialize and use `ssize_t n;`
- Check results:
  - if (fd < 0) { perror("open source"); return 1; }
  - if (n < 0) { perror("read"); close(fd); return 1; }
  - if (fd1 < 0) { perror("open target"); close(fd); return 1; }
  - if (write(fd1, buffer, n) != n) { perror("write"); }
- Close descriptors: `close(fd); close(fd1);`




