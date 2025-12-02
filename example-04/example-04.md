# Example 04 – Duplicating File Descriptors with dup2()

## Purpose

This example demonstrates how to duplicate an existing file descriptor to a specific target descriptor number using the POSIX function dup2(). It shows how the operating system can create an alias for an open file description and how the returned descriptor values behave.

## System Calls / Functions Used

- open(2) (fcntl.h) — open a file and obtain a file descriptor.
- dup2(2) (unistd.h) — duplicate a file descriptor to a specified target descriptor.
- printf (stdio.h) — formatted output to stdout (used here for demonstration).
- close(2) (unistd.h) — (recommended) close file descriptors when finished.
- Headers included in the source:
  - #include <unistd.h>
  - #include <fcntl.h>
  - #include <sys/types.h>
  - #include <sys/stat.h>
  - #include <stdio.h>

## How It Works

1. The program calls `open("dup", O_RDONLY)` to open a file named "dup" for reading. The returned file descriptor is stored in `fd`.
2. It prints the original file descriptor value (e.g., "OLD File Descriptor: 3") so you can observe the descriptor assigned by the kernel.
3. The call `dup2(fd, 7)` duplicates the file descriptor `fd` onto descriptor number 7:
   - If descriptor 7 is already open, the kernel first closes it and then makes descriptor 7 refer to the same open file description as `fd`.
   - If the duplication is successful, `dup2()` returns the new descriptor value (which should be 7). On error, it returns -1 and sets errno.
   - If `fd` equals the target (7), `dup2()` returns `fd` without closing it.
4. The program prints the new file descriptor returned by `dup2()` (e.g., "NEW File Descriptor: 7").
5. The program exits. (Note: the current source does not explicitly close descriptors before exiting; the OS will close them on process termination, but explicit close() calls are recommended.)

## How to Compile and Run

Compile:
$ gcc main.c -o app

Run:
$ ./app

Expected behavior:
- If the file "dup" exists and open() succeeds, you will see two printed lines showing the old and new file descriptor numbers. Example:
  OLD File Descriptor: 3
  NEW File Descriptor: 7
- If open() or dup2() fail, the program currently does not print errors; you may see -1 as the returned descriptor for failures.

## Recommended Improvements and Notes

- Check return values:
  - Verify `fd = open(...)` did not return -1 before using it.
  - Verify `dup2()` returned a non-negative value; handle errors with `perror()` or by printing `strerror(errno)`.
- Close descriptors when done: call `close(fd);` and, if different, `close(fd1);` to release resources explicitly.
- Use symbolic constants when appropriate: duplicating onto standard descriptors (e.g., `STDIN_FILENO`, `STDOUT_FILENO`, `STDERR_FILENO`) is common for redirection tasks.
- Avoid hard-coding descriptor numbers unless you intend to use a specific descriptor index. Descriptor numbers are process-specific and the kernel typically assigns small integers (3,4,...) for newly opened files.
- Be aware that `dup2(target)` will close the target descriptor if it is open, which may affect other parts of the program if that descriptor was used elsewhere.
- For safer and more portable printing of descriptor values and error messages, adopt English messages and structured error handling (the repository requires English documentation).

This explanation follows the repository guidelines: C implementation, English documentation, and the required explanation.md sections (Purpose, System Calls / Functions Used, How It Works, How to Compile and Run).
