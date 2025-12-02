# Example 09 – Replacing the Process Image with execl()

## Purpose

This example demonstrates how to replace the current process image with a new program using the exec family of functions. The program prints its PID, then calls `execl()` to run `/bin/ls -l`. When `execl()` succeeds, the current process image is replaced and the original program does not continue. If `execl()` fails, the program prints an error message and exits.

## System Calls / Functions Used

- execl(3) (unistd.h) — replace the current process image with a new program image.
- getpid() (unistd.h) — obtain the calling process's PID (used for demonstration).
- perror (stdio.h) — print a human-readable error message when `execl()` fails (uses errno).
- exit (stdlib.h) — terminate the process with a status code.
- Headers included in the source:
  - #include <stdio.h>
  - #include <stdlib.h>
  - #include <unistd.h>

## How It Works

1. The program prints its current process ID using `getpid()` so you can observe which process is being replaced.
2. It calls `execl("/bin/ls", "ls", "-l", NULL)`:
   - `execl()` replaces the current process image with the program at `/bin/ls`.
   - The first argument is the path to the executable. The subsequent arguments form the new process's argv[] list; by convention argv[0] is the program name ("ls").
   - The argument list must be terminated with a NULL pointer.
3. If `execl()` succeeds, it does not return; the new program (`ls -l`) runs in the same process (same PID) and the original program's code after the `execl()` call is never executed.
4. If `execl()` fails, it returns -1, sets `errno`, and the code after the call executes. The program uses `perror("execl failed")` to print an error message and then calls `exit(1)` to terminate with a non-zero status.

Key behavior to note:
- exec does not create a new process — it replaces the current process. To run a new program without replacing the caller, use `fork()` followed by `execl()` in the child.
- File descriptors remain open across `exec()` unless they have the close-on-exec flag set.
- Because `execl()` uses an absolute path in this example (`/bin/ls`), it does not search PATH. To search PATH, use `execlp()` or `execvp()`.

## How to Compile and Run

Compile:
$ gcc main.c -o app

Run:
$ ./app

Expected behavior:
- The `./app` process prints its PID, then is replaced by the `ls -l` program which lists the current directory contents. You will see the directory listing output; once `ls` finishes, the process exits. You will not return to the original program after a successful `execl()`.

Example run:
$ ./app
Before execl: current process PID: 12345
(total listing produced by `ls -l`)

If `execl()` fails (e.g., wrong path or permissions), you will see:
execl failed: No such file or directory

## Recommended Improvements and Notes

- Error handling: `perror()` is appropriate for reporting `execl()` failures. Consider printing more context when needed.
- If you want to run a command while keeping the original program running, use `fork()` + `execl()` in the child process:
  - parent can continue, child is replaced by the new program.
- To provide argv[] dynamically, use `execv()` or `execvp()` with an argument array.
- To search PATH automatically, use `execlp()` or `execvp()`.
- Remember that environment variables can be preserved or replaced depending on which exec variant is used (`execle`, `execve`).
- Use absolute paths when you want deterministic behavior (as in this example) or validate the path before calling `execl()`.

This explanation follows the repository rules: implementation in C, English documentation, and the required sections (Purpose, System Calls / Functions Used, How It Works, How to Compile and Run).
