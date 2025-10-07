#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#ifndef NUM_THREADS
#define NUM_THREADS 5
#endif

sem_t sem;

void *funcao(void *argumentos)
{
    sem_wait(&sem);
    printf("OLA\n");
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    sem_init(&sem, 0, 0);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, funcao, NULL);
    }
    printf("Thread principal a esperar a criação das threads\n");

    for (int i = 0; i < NUM_THREADS; i++)
        sem_post(&sem);

    // Esperar todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    sem_destroy(&sem);

    return 0;
}
