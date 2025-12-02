#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {

    int fd, fd1;
    fd = open("dup", O_RDONLY);
    printf("OLD File Descriptor: %d\n", fd);

    fd1 = dup2(fd, 7);
    printf("NEW File Descriptor: %d\n", fd1);

    return 0;
}