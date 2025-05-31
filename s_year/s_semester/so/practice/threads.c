#include <stdio.h>
#include <pthread.h>

int x = 0;
void *maisx(void *args)
{
    int id = *(int *)args;
    x = x + id;
}

int main()
{
    pthread_t th[3];
    pthread_mutex_t mutex_lock;
    int ids[3] = {1, 3, 5};

    pthread_mutex_init(&mutex_lock, NULL);

    for (int i = 0; i < 3; i++)
        pthread_create(&th[i], NULL, maisx, &ids[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(th[i], NULL);

    printf("x = %d\n", x);
}