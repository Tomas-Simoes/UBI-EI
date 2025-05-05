#include <stdio.h>
#include <pthread.h>

#ifndef NUM_THREADS
#define NUM_THREADS 5
#endif

int x = 1;

void *thread(void **args)
{
    while (x == 1)
    {
    }

    printf("this is from thread");
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, thread, NULL);

    scanf("%d", &x);
}