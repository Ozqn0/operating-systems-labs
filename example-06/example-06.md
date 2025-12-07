# Example 06 – Creating Two Children and Using waitpid()

## Purpose

This example demonstrates creating multiple child processes using `fork()` and basic parent-child synchronization using `waitpid()`. It shows how the parent can create two children, retrieve their process IDs, and wait for a specific child to terminate before continuing.

## System Calls / Functions Used

- fork(2) (unistd.h) — create a new process by duplicating the calling process.
- waitpid(2) (sys/wait.h) — wait for a specific child process to change state (used here to wait for the first child).
- getpid() (unistd.h) — get the calling process's PID.
- getppid() (unistd.h) — get the parent process's PID.
- printf (stdio.h) — formatted output to stdout.
- close / exit (stdlib.h) — exit the program (used indirectly).
- Headers used in the source:
  - #include <unistd.h>
  - #include <sys/types.h>
  - #include <stdio.h>
  - #include <sys/wait.h>

## How It Works

1. The program prints "Before fork" and calls `fork()` the first time, storing the return value in `p`.
   - If `p == 0`, this is the first child: it prints its own PID and its parent's PID, then continues to the end and exits.
   - If `p > 0`, this is the parent: it proceeds to create a second child.
   - If `p < 0`, `fork()` failed (not handled in the current code).
2. The parent calls `fork()` a second time and stores the return value in `q`.
   - If `q == 0`, this is the second child: it prints its own PID and its parent's PID, then continues to the end and exits.
   - If `q > 0`, this is still the parent: it now has two child PIDs available in `p` and `q`.
   - If `q < 0`, the second `fork()` failed (not handled in the current code).
3. In the parent branch after the second `fork()`, the program calls `waitpid(p, NULL, 0)` to wait for the first child to terminate. After `waitpid()` returns, the parent prints its PID and the stored PIDs of the first and second children.
4. Each process then reaches the program end and exits. The parent reaps the first child explicitly; the second child may already have terminated or may still be running when the parent prints information.

Important runtime characteristics:
- The order of output between parent and children is nondeterministic and depends on scheduler timing.
- The program currently waits only for the first child (`p`) using `waitpid(p, NULL, 0)`. The second child (`q`) is not explicitly waited for in the code; if it terminates earlier than the parent's exit and is not reaped, it can briefly become a zombie until the parent exits or reaps it.
- Because of stdio buffering, prints may interleave; using newline-terminated strings or explicit `fflush(stdout)` helps ensure timely output.

## How to Compile and Run

Compile:
$ gcc main.c -o app

Run:
$ ./app

Sample possible outputs (ordering may vary):
Before fork
I am first child havin id: 12345
My parent PID is: 12344
I am second child having PID: 12346
Second child's parent PID is: 12344
I am parent havin PID: 12344
My first child PID is: 12345
My second child PID is: 12346

Or (different scheduling):
Before fork
I am parent havin PID: 12344
My first child PID is: 12345
My second child PID is: 12346
I am first child havin id: 12345
I am second child having PID: 12346





