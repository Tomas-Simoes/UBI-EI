#include <stdio.h>
#include <pthread.h>

#ifndef NUM_THREADS
#define NUM_THREADS 5
#endif

typedef struct
{
    int a;
    float b;
} ThreadArgs;

ThreadArgs TA;

void *threadFunc(void **args)
{
    int id = *(int *)args;
    printf("Thread %d\n", id);

    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int i, ids[NUM_THREADS];

    for (i = 0; i < NUM_THREADS; i++)
        ids[i] = i;

    for (i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, threadFunc, &ids[i]);

    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    return 0;
}
