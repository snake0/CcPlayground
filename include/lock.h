//
// Created by SNAKE on 2019-08-27.
//
#ifndef LOCK_H
#define LOCK_H
#ifndef MCT_CACHELINE_BYTES
#define MCT_CACHELINE_BYTES 64
#endif

#include "csapp.h"

static inline uint32_t xchg(volatile uint32_t* addr, uint32_t newval) {
    uint32_t result;

    // The + in "+m" denotes a read-modify-write operand.
    asm volatile("lock; xchgl %0, %1"
    : "+m"(*addr), "=a"(result)
    : "1"(newval)
    : "cc");
    return result;
}

/* spinlock */
typedef struct {
    volatile unsigned locked;
} spinlock_t;

inline void spinlock_init(spinlock_t* lock) {
    lock->locked = 0;
}

void spinlock_lock(spinlock_t* lock) {
    while (xchg(&lock->locked, 1) != 0)
        asm volatile("pause");
}

inline void spinlock_unlock(spinlock_t* lock) {
    xchg(&lock->locked, 0);
}

/* mcslock */
static struct _mcslock_node {
    struct _mcslock_node* volatile next; /*next one waiting the lock*/
    volatile char wait;                  /*should wait or not*/
} __attribute__((__aligned__(MCT_CACHELINE_BYTES))) mcslock_node;

typedef struct {
    struct _mcslock_node* volatile tail;        /*queue tail*/
} mcslock_t;


inline void mcs_lock_init(mcslock_t* lock) {
    lock->tail = NULL;
}

#endif