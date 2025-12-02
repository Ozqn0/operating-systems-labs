# Example 07 – Demonstrating Process Timing and Orphan Reparenting

## Purpose

This example demonstrates basic process creation with `fork()` and illustrates timing effects between parent and child processes. By using different `sleep()` durations for parent and child, the example typically shows the parent exiting before the child, which makes the child an orphan that is reparented to the init/systemd process. It also highlights nondeterministic ordering of output and the need for proper synchronization when required.

## System Calls / Functions Used

- fork(2) (unistd.h) — create a new process by duplicating the calling process.
- sleep(3) (unistd.h) — suspend execution for a number of seconds.
- getpid() (unistd.h) — obtain the calling process's PID.
- getppid() (unistd.h) — obtain the parent process's PID.
- printf (stdio.h) — formatted output to stdout.
- Headers in the source:
  - #include <stdio.h>
  - #include <unistd.h>
  - #include <sys/types.h>

## How It Works

1. The program calls `fork()` and stores the return value in `p`:
   - In the child process, `fork()` returns 0.
   - In the parent process, `fork()` returns the child's PID (positive).
2. The child branch calls `sleep(10)` to pause for 10 seconds, then prints its PID and current parent PID (`getppid()`).
3. The parent branch calls `sleep(2)` to pause for 2 seconds, then prints its PID and the child's PID (the return value from `fork()`).
4. Because the parent sleeps a shorter time, it usually exits before the child wakes. When the child wakes and calls `getppid()`, its parent may have already exited, so the kernel reassigns the child's parent to the system init process (PID 1) or the appropriate reaper (e.g., systemd). This demonstrates orphan reparenting.
5. Output ordering is not strictly guaranteed; scheduling and timing may change which lines appear first. Standard I/O buffering can also affect appearances of prints.

## How to Compile and Run

Compile:
$ gcc main.c -o app

Run:
$ ./app

Example typical output (parent exits before child):
Before fork
I am parent having PID: 12344
My child PID is: 12345
I am child having PID: 12345
My parent PID is: 1

Or (different timing / scheduler):
Before fork
I am child having PID: 12345
My parent PID is: 12344
I am parent having PID: 12344
My child PID is: 12345

Note: The parent PID printed by the child will be the original parent's PID if the parent is still running; otherwise it will typically be 1 (or another reaper PID depending on the system).

## Recommended Improvements and Notes

- Check `fork()` return value for errors:
  - if (p < 0) { perror("fork"); return 1; }
- Use `waitpid()` in the parent to wait for the child if you want to avoid orphans and ensure deterministic ordering:
  - in parent: `waitpid(p, NULL, 0);`
- Use newline-terminated strings and/or `fflush(stdout)` to reduce surprises from stdio buffering when demonstrating ordering.
- For clearer demonstration of reparenting, you can increase the child's sleep and decrease the parent's sleep, or explicitly `exit()` the parent after printing.
- Remember that on modern systems `getppid()` may return the PID of a process other than 1 depending on the reaper process model (systemd or other service managers).
- Add English comments to the source code so the behavior is clear to all students, and include error handling where appropriate.

This explanation follows the repository rules: the code is C, explanations are in English, and the file includes Purpose, System Calls / Functions Used, How It Works, How to Compile and Run, and Recommended Improvements.
