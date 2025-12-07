# Example 08 – Parent Sleeps While Child Runs (Demonstrating Execution Ordering)

## Purpose

This example demonstrates process creation with `fork()` and highlights how relative timing (using `sleep()`) affects the observed ordering of output between parent and child processes. It is intended to show that the child can run and print before the parent, and that output ordering and parent/child relationships depend on scheduling and timing.

## System Calls / Functions Used

- fork(2) (unistd.h) — create a new process by duplicating the calling process.
- sleep(3) (unistd.h) — suspend execution for a number of seconds.
- getpid() (unistd.h) — obtain the calling process's PID.
- getppid() (unistd.h) — obtain the parent's PID.
- printf (stdio.h) — formatted output to stdout.
- Headers included in the source:
  - #include <stdio.h>
  - #include <unistd.h>
  - #include <sys/types.h>

## How It Works

1. The program calls `fork()` and stores the returned value in `p`.
   - In the child process, `fork()` returns 0.
   - In the parent process, `fork()` returns the child's PID (a positive integer).
2. The child branch executes immediately: it prints the child's PID and the parent's PID using `getpid()` and `getppid()`.
3. The parent branch calls `sleep(10)` to pause for 10 seconds and then prints the parent's PID and the child's PID.
4. Because the child does not sleep and the parent sleeps for 10 seconds, the child usually prints first. The child’s `getppid()` call will typically return the original parent's PID if the parent has not exited yet. If the parent exits before the child prints, the child may be reparented and `getppid()` can return a different PID (e.g., 1 or the system reaper).
5. The program then exits. Note that the ordering of prints is not strictly guaranteed across runs because of OS scheduling and stdio buffering behavior.

## Important Behavior and Notes

- Output ordering is nondeterministic: changes in scheduling, system load, or buffering may change which process’s messages appear first.
- The program does not check the return value of `fork()` for errors. If `fork()` fails (returns -1), proper error handling should be added.
- Standard I/O buffering may cause outputs to appear delayed or combined. Ensuring newline-terminated strings or calling `fflush(stdout)` can help make output appear when expected.
- The child's `getppid()` will show the parent's PID only if the parent is still alive at that moment. If the parent has already exited, the kernel will reparent the child to the system reaper process (often PID 1 or a dedicated reaper), and `getppid()` will reflect that.


## How to Compile and Run

Compile:
$ gcc main.c -o app

Run:
$ ./app

Typical output (child runs before parent):
Before fork
I am child having PID: 12345
My parent PID is: 12344
I am parent having PID: 12344
My child PID is: 12345

Because scheduling is nondeterministic, output order may vary across runs.



