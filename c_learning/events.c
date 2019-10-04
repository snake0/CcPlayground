//
// Created by SNAKE on 10/4/19.
//

#include "lock.h"
#include "include_for_c.h"

#define THREADS 2
pthread_t threads[THREADS];

pthread_barrier_t barrier;


static int events = 5;
spinlock_t lk = {0};

int get_event(void) {
    spinlock_lock(&lk);
    if (events == 0) {
        spinlock_unlock(&lk);
        return 0;
    }
    --events;
    spinlock_unlock(&lk);
    return 1;
}

void *thread(void *arg) {
    pthread_barrier_wait(&barrier);

    while (get_event()) {
        sleep(1);
        printf("%d, %d\n", (int) pthread_self(), events);
    }
    return (void *) 0;
}


int main() {
    pthread_barrier_init(&barrier, 0, THREADS);

    for (int i = 0; i < THREADS; ++i) {
        pthread_create(&threads[i], NULL, thread, NULL);
    }
    for (int i = 0; i < THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
}