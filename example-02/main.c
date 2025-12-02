#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(){

    int n,fd,fd1;
    char buffer[50];

    fd = open("text.txt",O_RDONLY); // Open file "text.txt" for reading
    n = read(fd,buffer,10);        // Read up to 50 bytes from
    printf("Number of bytes read: %d\n",n); // Print the number of bytes read

    fd1 = open("target",O_CREAT | O_WRONLY,0642); // Open (or create) file "target" for writing

    write(fd1,buffer,n);          // Write the read bytes to stdout
    return 0;
}