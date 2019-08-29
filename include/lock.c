//
// Created by SNAKE on 2019-08-28.
//

//
// Created by SNAKE on 2019-08-27.
//

#include "lock.h"
#include "barrier.h"
#include "sync_prim.h"

static inline uint32_t test_and_set(volatile uint32_t* addr, uint32_t newval) {
    uint32_t result;

    // The + in "+m" denotes a read-modify-write operand.
    asm volatile("lock; xchgl %0, %1"
    : "+m"(*addr), "=a"(result)
    : "1"(newval)
    : "cc");
    return result;
}

static inline uint32_t compare_and_swap(volatile uint32_t* addr, uint32_t oldval, uint32_t newval) {
    unsigned char ret;

    // Note that sete sets a ’byte’ not the word
    asm volatile (
    "lock\n"  // atomicity
    " cmpxchgl %2,%1\n"  //cmpxchg instruction
    " sete %0\n"         //sete instruction
    : "=q"(ret), "=m"(*addr) //output
    : "r"(newval), "m"(*addr), "a"(oldval) //input
    : "cc"); //destroyed

    return ret;
}

uint32_t fetch_and_add(volatile uint32_t* addr) {
    return __sync_fetch_and_add(addr, 1);
}


/************ spinlock *************/
void spinlock_lock(spinlock_t* lk) {
    while (test_and_set(&lk->locked, 1) != 0)
        asm volatile("pause");
}

/************* ticketlock *************/

void ticketlock_lock(ticketlock_t* lk) {
    int myturn = fetch_and_add(&lk->ticket);
    while (myturn != lk->turn);
}


/************* mcslock *************/
void mcslock_lock(mcslock_t* lock, struct _mcslock_node* mynode) {
    struct _mcslock_node* pre;
    mynode->next = NULL;
    mynode->wait = 1;

    /*atomic: {pre=lock->tail; tail=node;} */
    pre = fetch_and_store(&lock->tail, mynode);
    if (pre == NULL) {
        /* It's free, and taken by me */
        return;
    }

    /* it's hold by others. queue up and spin on the node of myself */
    pre->next = mynode;
    smp_wmb();
    while (mynode->wait) {
        /* nop or some power saving instruction like "pause" on x86*/
        cpu_relax();
    }
}

inline void mcslock_unlock(mcslock_t* lock, struct _mcslock_node* mynode) {
    if (mynode->next == NULL) {
        /*
         * I'm the last one temporally, now race with other new requester:
         * They may try to fetch_and_store(&lock->tail, their_node),
         * while I'll try to "set lock->tail=me, if I'm still the last one"
         */
        if (compare_and_store(&lock->tail, mynode, NULL)) {
            return;
        }
        /* we failed the race, someone else will wait afer me soon
         * wait util he complete mcs_lock: "pre->next = mynode;"
         */
        while (mynode->next == NULL) {
            /* usally we don't need cpu_relax because the follower need only
             * several instructions to put himself on my "next" to free myself
             * But in case the follower got interrupted or TLB miss or page fault ...
             */
            smp_rmb();
            cpu_relax();
        }
    } /*if (mynode->next == NULL)*/

    /* here I'm sure someone is waiting after me, pass the lock
       to him and return*/
    mynode->next->wait = 0;
    return;
}
