#include <stdio.h>
#include <pthread.h>
#ifndef NUM_THREADS
#define NUM_THREADS 5
#endif

void *funcao(void *argumentos)
{
    printf("\nOLA\n");
    return (NULL);
}
int main()
{
    pthread_t threads[NUM_THREADS];
    int i;
    for (i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, funcao, NULL);
    printf("Thread principal a esperar a criação das threads\n");
    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL); /* Esperar a junção das threads */
    return 0;                           /* O programa chegará aqui. */
}