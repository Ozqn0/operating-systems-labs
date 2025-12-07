# Example 05 – Process Creation with fork()

## Purpose

This example demonstrates how to create a new process using the POSIX `fork()` system call. It shows how the parent and child processes receive different return values from `fork()`, how to obtain process identifiers with `getpid()` and `getppid()`, and how both processes continue execution from the point of the `fork()` call.

## System Calls / Functions Used

- fork(2) (unistd.h) — create a new process by duplicating the calling process.
- getpid() (unistd.h) — obtain the calling process's PID.
- getppid() (unistd.h) — obtain the parent's PID.
- printf (stdio.h) — formatted output to stdout.
- Types and headers used:
  - #include <unistd.h>
  - #include <sys/types.h>
  - #include <stdio.h>

## How It Works

1. The program prints "Before fork" and then calls `fork()`.
2. `fork()` creates a child process:
   - In the child process `fork()` returns 0.
   - In the parent process `fork()` returns the child's PID (a positive integer).
   - On error, `fork()` returns -1 (not handled in this code).
3. The program uses the return value `q` to distinguish parent and child:
   - If `q == 0` (child): the child prints its own PID (`getpid()`) and its parent's PID (`getppid()`).
   - Else (parent): the parent prints the child's PID (`q`) and its own PID (`getpid()`).
4. Both processes then execute the final `printf("Common\n");` statement and exit.
5. Note: The order of printed lines from parent and child is nondeterministic — scheduling decides which process runs first. Also, because of stdio buffering, output may appear in different orders unless lines end with a newline and streams are flushed.

Important runtime behaviors:
- No error handling for `fork()` is present. If `fork()` fails, the program will treat `q` as -1 and go to the `else` branch, which is incorrect.
- The parent does not wait for the child (no `wait()` call). This can leave a brief period where a defunct (zombie) child exists until the parent exits or reaps it.
- Outputs from parent and child may interleave unpredictably.


## How to Compile and Run

Compile:
```bash
$ gcc main.c -o app
```

Run:
```bash
$ ./app
```

Example possible outputs (order may vary):
- If child runs first:
```
Before fork
I am child havin id: 12345
My parent id is: 12344
Common
My child id is: 12345
I am parent havin id: 12344
Common
```
- If parent runs first:
```
Before fork
My child id is: 12345
I am parent havin id: 12344
Common
I am child havin id: 12345
My parent id is: 12344
Common
```

Notes:
- The program prints two "Common" lines because both parent and child execute that statement.
- For clearer lab output and to meet repository guidelines, consider changing printed messages to grammatically consistent English (e.g., "I am child with pid: %d" and "I am parent with pid: %d") and add error handling as suggested.



