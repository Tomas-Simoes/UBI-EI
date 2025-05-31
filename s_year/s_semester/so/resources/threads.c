//#include <pthread .h>
//#include <assert .h>
// or use compiler flag -I /usr/include
//correct the following code so that the assert does not give an error.
//correct code with obne semaphore an one mutex

#include <pthread.h>
#include <assert.h>
int shared = 0;
int *ptr=NULL;
void *thread1(void *arg){
    register int tmp;
    ptr = &shared;
    tmp = shared;
    tmp++;
    shared = tmp;
    return NULL;
}
void *thread2(void *arg){
    register int tmp;
    if (ptr){
        tmp = shared;
        tmp++;
        shared = tmp;
    }
    return NULL;
}
int main(void)
{
    pthread_t t[2];
    pthread_create(&t[0], NULL, thread1, NULL);
    pthread_create(&t[1], NULL, thread2, NULL);
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    assert(shared == 2);
    return 0;
}
