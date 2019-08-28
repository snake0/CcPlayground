#include "lock.h"
#include "diy.h"

#define THREADS 20
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//ticketlock_t lk;
mcslock_t lk;

void* thread(void* args) {
    int* str = (int*) args;
    struct _mcslock_node my_lock_node;
//    ticketlock_lock(&lk);
//    pthread_mutex_lock(&mutex);
//    mcslock_lock(&lk, &my_lock_node);
    printf("%d ", ++*str);
//    ticketlock_unlock(&lk);
//    pthread_mutex_unlock(&mutex);
//    mcslock_unlock(&lk, &my_lock_node);

    return 0;
}

void test_memcpy() {
    char* p = malloc(100);
    p[0] = '1';
    p[1] = '2';
    p[2] = '3';
    p[3] = '4';
    p[4] = '5';
    const int start = 2;
    const int len = 5;
    fast_memcpy(p + start, p, len);
    prstr(p, len);
    prstr(p + start, len);
}

int main() {
//    ticketlock_init(&lk);
//    mcslock_init(&lk);
//    pthread_t pids[THREADS];
//    for (int i = 0; i < THREADS; ++i)
//        pthread_create(&pids[i], NULL, worker, (void*) &common);
//    for (int i = 0; i < THREADS; ++i)
//        pthread_join(pids[i], NULL);
    test_memcpy();
}