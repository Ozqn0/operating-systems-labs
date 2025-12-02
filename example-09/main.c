#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Before execl: current process PID: %d\n", getpid());

    // Replace current process image with "ls -l"
    execl("/bin/ls", "ls", "-l", NULL);

    // If execl() fails
    perror("execl failed");
    exit(1);
}