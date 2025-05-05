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

void *thread(void **args)
{
    ThreadArgs *in = (ThreadArgs *)args;
    printf("%d %f\n", in->a, in->b);
}

int main()
{
    TA.a = 5;
    TA.b = 2.5;

    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, thread, (void *)&TA);
}