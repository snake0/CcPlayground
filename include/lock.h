//
// Created by SNAKE on 2019-08-27.
//
#ifndef LOCK_H
#define LOCK_H


#include "csapp.h"
#include "sync_prim.h"

/************ spinlock *************/
typedef struct __spinlock_t {
    volatile uint32_t locked;
} spinlock_t;

inline void spinlock_init(spinlock_t* lk) { lk->locked = 0; }

void spinlock_lock(spinlock_t* lk);

inline void spinlock_unlock(spinlock_t* lk) { lk->locked = 0; }

/************* ticketlock *************/
typedef struct __ticketlock_t {
    uint32_t ticket;
    uint32_t turn;
} ticketlock_t;

inline void ticketlock_init(ticketlock_t* lk) { memset(lk, 0, sizeof(ticketlock_t)); }

void ticketlock_lock(ticketlock_t* lk);

inline void ticketlock_unlock(ticketlock_t* lk) { ++lk->turn; }

/************* mcslock *************/
static struct _mcslock_node {
    struct _mcslock_node* volatile next; /* next one waiting the lk */
    volatile char wait;                  /* should wait or not */
} __attribute__((__aligned__(MCT_CACHELINE_BYTES))) mcslock_node;

typedef struct __mcslock_t {
    struct _mcslock_node* volatile tail;        /* queue tail */
} mcslock_t;


inline void mcslock_init(mcslock_t* lk) { lk->tail = NULL; }

void mcslock_lock(mcslock_t* lk, struct _mcslock_node* mynode);
void mcslock_unlock(mcslock_t* lk, struct _mcslock_node* mynode);

#endif