//
// Created by SNAKE on 2019-08-29.
//

#include "lock.h"

#define THREADS 20
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
ticketlock_t lk;
//mcslock_t lk;

void* thread(void* args) {
    int* str = (int*) args;
    struct _mcslock_node my_lock_node;
    ticketlock_lock(&lk);
//    pthread_mutex_lock(&mutex);
//    mcslock_lock(&lk, &my_lock_node);
    printf("%d ", ++*str);
    ticketlock_unlock(&lk);
//    pthread_mutex_unlock(&mutex);
//    mcslock_unlock(&lk, &my_lock_node);

    return 0;
}

int common = 0;

int main() {
//    ticketlock_init(&lk);
    ticketlock_init(&lk);
    pthread_t pids[THREADS];
    for (int i = 0; i < THREADS; ++i)
        pthread_create(&pids[i], NULL, thread, (void*) &common);
//    for (int i = 0; i < THREADS; ++i)
//        pthread_join(pids[i], NULL);
    printf("done\n");
}