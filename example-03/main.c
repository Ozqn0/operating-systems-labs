#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h> 

int main()
{
    int n, f;
    off_t f1; 
    char buff[10];

    f = open("seeking", O_RDWR);
    
    if (f < 0) {
        perror("Dosya açma hatası");
        exit(1);
    }

    f1 = lseek(f, 10, SEEK_SET);

    if (f1 == (off_t)-1) {
        perror("Lseek hatası");
        close(f);
        exit(1);
    }

    printf("Pointer şu an %ld. pozisyonda\n", (long)f1);
    n = read(f, buff, 10);
    
    if (n < 0) {
        perror("Okuma hatası");
        close(f);
        exit(1);
    }
    write(STDOUT_FILENO, buff, n); 
    write(STDOUT_FILENO, "\n", 1);
    close(f);

    return 0;
}