#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    pid_t p, q;

    printf("Before fork\n");

    p = fork();

    if (p == 0) {
        printf("I am first child havin id: %d\n", getpid());
        printf("My parent PID is: %d\n", getppid());
    }
    else {
        q = fork();

        if (q == 0) {
            printf("I am second child having PID: %d\n", getpid());
            printf("Second child's parent PID is: %d\n", getppid());
        }
        else {
            waitpid(p, NULL, 0);
            printf("I am parent havin PID: %d\n", getpid());
            printf("My first child PID is: %d\n", p);
            printf("My second child PID is: %d\n", q);
        }
    }

    return 0;
}