//
// Created by SNAKE on 2019-08-27.
//
#ifndef LOCK_H
#define LOCK_H
#ifndef MCT_CACHELINE_BYTES
#define MCT_CACHELINE_BYTES 64
#endif

#include "csapp.h"

/************* primitives *************/
inline uint32_t test_and_set(volatile uint32_t* addr, uint32_t newval);

inline uint32_t compare_and_swap(volatile uint32_t* addr, uint32_t oldval, uint32_t newval);

inline uint32_t fetch_and_add(volatile uint32_t* addr);


/************ spinlock *************/
typedef struct {
    volatile uint32_t locked;
} spinlock_t;

inline void spinlock_init(spinlock_t* lk);

void spinlock_lock(spinlock_t* lk);

void spinlock_unlock(spinlock_t* lk);

/************* ticketlock *************/
typedef struct {
    uint32_t ticket;
    uint32_t turn;
} ticketlock_t;

inline void ticketlock_init(ticketlock_t* lk);

void ticketlock_lock(ticketlock_t* lk);

inline void ticketlock_unlock(ticketlock_t* lk);

/************* mcslock *************/
static struct _mcslock_node {
    struct _mcslock_node* volatile next; /*************next one waiting the lk*************/
    volatile char wait;                  /*************should wait or not*************/
} __attribute__((__aligned__(MCT_CACHELINE_BYTES))) mcslock_node;

typedef struct {
    struct _mcslock_node* volatile tail;        /*************queue tail*************/
} mcslock_t;


inline void mcs_lock_init(mcslock_t* lk);

#endif