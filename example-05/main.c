#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    pid_t q;

    printf("Before fork\n");

    q = fork();

    if (q == 0) {
        printf("I am child havin id: %d\n", getpid());
        printf("My parent id is: %d\n", getppid());
    }
    else {
        printf("My child id is: %d\n", q);
        printf("I am parent havin id: %d\n", getpid());
    }

    printf("Common\n");
    return 0;
}