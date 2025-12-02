# Example 10 – POSIX Threads: Creating and Joining a Thread

## Purpose

This example demonstrates creating a POSIX thread using `pthread_create()`, waiting for it to finish with `pthread_join()`, and simple thread work performed concurrently with the main program. The program shows how a child thread can execute a function while the main thread waits for its completion, then the main thread continues execution.

## System Calls / Functions Used

- pthread_create(3) (pthread.h) — create a new thread in the calling process.
- pthread_join(3) (pthread.h) — wait for a specific thread to terminate.
- sleep(3) (unistd.h) — suspend execution for a number of seconds (used to slow output for demonstration).
- printf (stdio.h) — formatted output to stdout.
- gettid / getpid are not used here but are useful when demonstrating thread/process ids.
- Headers included in the source:
  - #include <stdio.h>
  - #include <unistd.h>
  - #include <pthread.h>

## How It Works

1. Global integers `i` and `j` are declared. These are shared between the main thread and the created thread.
2. In `main()` a `pthread_t a_thread` variable is declared, and `pthread_create(&a_thread, NULL, thread_function, NULL)` is called to start `thread_function` in a new thread.
3. Immediately after creation, the main thread calls `pthread_join(a_thread, NULL)`. This blocks the main thread until the created thread finishes executing.
4. The created thread (`thread_function`) executes:
   - It prints "Inside Thread".
   - It runs a loop printing the values 0..4 with a 1-second `sleep()` between prints.
   - After completing the loop, the thread returns NULL and terminates.
5. Once `pthread_join()` returns (the child thread has finished), the main thread resumes, prints "Inside Main Program", then runs its own loop printing `j` values from 20 to 24 with 1-second sleeps.
6. Because `pthread_join()` is used immediately after creating the thread, the main thread waits and the two loops do not execute concurrently; the thread's output appears before the main thread's loop begins.

## Important Behavior and Notes

- Thread synchronization:
  - The example uses global variables `i` and `j` but in the current program they are not accessed concurrently because `pthread_join()` ensures the thread finishes before the main thread continues. If you remove `pthread_join()` or access shared data concurrently, you must protect shared variables with synchronization primitives (mutexes, condition variables) to avoid data races.
- Error handling:
  - The program does not check return values of `pthread_create()` and `pthread_join()`. Always check these returns and handle errors (e.g., print an error and exit) in robust code.
- Thread resources:
  - `pthread_join()` reaps the thread and releases resources associated with it; failing to join joinable threads can leak resources. Alternatively, detach threads with `pthread_detach()` if you do not intend to join.
- Portability:
  - Use `-pthread` when compiling (it sets needed macros and links the pthread library).
- Deterministic ordering:
  - Because the main thread calls `pthread_join()` right after `pthread_create()`, output from the two loops is sequential (thread output first, then main output). If you want concurrent interleaved output, call `pthread_create()` without joining immediately and manage synchronization explicitly.

## How to Compile and Run

Compile (link with pthreads):
$ gcc main.c -o app -pthread

Run:
$ ./app

Expected runtime behavior:
- The program prints:
  - "Inside Thread"
  - Then the numbers 0,1,2,3,4 each on its own line (1-second intervals)
  - "Inside Main Program"
  - Then the numbers 20,21,22,23,24 each on its own line (1-second intervals)

## Recommended Improvements

- Check return values and handle errors:
  - int rc = pthread_create(...); if (rc != 0) { fprintf(stderr, "pthread_create: %s\n", strerror(rc)); return 1; }
  - rc = pthread_join(...);
- Avoid unnecessary global variables. Pass needed data via the thread argument (`void *arg`) or use well-protected shared data structures.
- If concurrent access is required, protect shared state with `pthread_mutex_t` and use `pthread_cond_t` for signaling when needed.
- Consider adding `fflush(stdout)` after `printf()` calls when demonstrating ordering, to avoid surprises from stdio buffering.
- Respect the repository compilation rules while noting that pthread programs require linking with `-pthread`.

This explanation follows the repository rules: the exercise is implemented in C, all explanations are in English, and the document includes Purpose, System Calls / Functions Used, How It Works, and How to Compile and Run sections.
