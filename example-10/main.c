#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *thread_function(void *arg);
int i, j;

int main()
{
    pthread_t a_thread;

    pthread_create(&a_thread, NULL, thread_function, NULL);
    pthread_join(a_thread, NULL);

    printf("Inside Main Program\n");

    for (j = 20; j < 25; j++)
    {
        printf("%d\n", j);
        sleep(1);
    }

    return 0;
}

void *thread_function(void *arg)
{
    printf("Inside Thread\n");

    for (i = 0; i < 5; i++)
    {
        printf("%d\n", i);
        sleep(1);
    }

    return NULL;
}