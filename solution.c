#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADS 10
#define HOLDING(l) (!!(l->locked))
#define CPUID(in, a, b, c, d)  asm("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

static int getcpuid(char* id, size_t max) {
    int i;
    unsigned long li, maxi, maxei, eax, ebx, ecx, edx, unused;

    CPUID (0, maxi, unused, unused, unused);
    maxi &= 0xffff;

    if (maxi < 3) {
        return -1;
    }
    CPUID(3, eax, ebx, ecx, edx);

    snprintf(id, max, "%08lx %08lx %08lx %08lx", eax, ebx, ecx, edx);
    fprintf(stdout, "get cpu id: %s/n", id);

    return 0;
}

static inline uint32_t xchg(volatile uint32_t* addr, uint32_t newval) {
    uint32_t result;

    // The + in "+m" denotes a read-modify-write operand.
    asm volatile("lock; xchgl %0, %1"
    : "+m"(*addr), "=a"(result)
    : "1"(newval)
    : "cc");
    return result;
}

struct spinlock {
    volatile unsigned locked;
};

static struct spinlock* lk;

struct spinlock* spinlock_init() {
    struct spinlock* lock = (struct spinlock*) malloc(sizeof(struct spinlock));
    lock->locked = 0;
    return lock;
}

void spinlock_lock(struct spinlock* lock) {
    while (xchg(&lock->locked, 1) != 0)
        asm volatile("pause");
}

void spinlock_unlock(struct spinlock* lock) { xchg(&lock->locked, 0); }

void spinlock_destroy(struct spinlock* lock) { free(lock); }

void* worker(void* args) {
    int* str = (int*) args;
    spinlock_lock(lk);
    char id;
//  getcpuid(&id, 100);
    spinlock_unlock(lk);

    return 0;
}

int common = 0;

int main() {
    lk = spinlock_init();
    pthread_t pids[THREADS];
    for (int i = 0; i < THREADS; ++i)
        pthread_create(&pids[i], NULL, worker, (void*) &common);
    for (int i = 0; i < THREADS; ++i)
        pthread_join(pids[i], NULL);
}