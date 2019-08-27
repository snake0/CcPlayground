#include "lock.h"

#define THREADS 20
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
ticketlock_t lk;

void* worker(void* args) {
    int* str = (int*) args;
    ticketlock_lock(&lk);
//    pthread_mutex_lock(&mutex);

    printf("%d ", ++*str);
    ticketlock_unlock(&lk);
//    pthread_mutex_unlock(&mutex);

    return 0;
}

int common = 0;

int main() {
    spinlock_init(&lk);
    pthread_t pids[THREADS];
    for (int i = 0; i < THREADS; ++i)
        pthread_create(&pids[i], NULL, worker, (void*) &common);
    for (int i = 0; i < THREADS; ++i)
        pthread_join(pids[i], NULL);
}