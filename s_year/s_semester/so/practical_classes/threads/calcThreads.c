#include <stdio.h>
#include <pthread.h>
#include <math.h>

#ifndef NUM_THREADS
#define NUM_THREADS 5
#endif

typedef struct
{
    int a;
    float b;
} ThreadArgs;

ThreadArgs TA;

double *sinThread(void **args)
{
    double x = *(double *)args;
    printf("sin^3(%f)\n", x);

    return pow(sin(x), 3.0);
}

double *cosThread(void **args)
{
    double x = *(double *)args;
    printf("sqrt(cos(%f))\n", x);

    return sqrt(cos(x));
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int i, ids[NUM_THREADS];

    pthread_create(&threads[i], NULL, threadFunc, &ids[i]);

    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    return 0;
}
