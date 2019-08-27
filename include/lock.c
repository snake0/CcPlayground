//
// Created by SNAKE on 2019-08-28.
//

//
// Created by SNAKE on 2019-08-27.
//

#include "lock.h"

/************* primitives *************/
uint32_t test_and_set(volatile uint32_t* addr, uint32_t newval) {
    uint32_t result;

    // The + in "+m" denotes a read-modify-write operand.
    asm volatile("lock; xchgl %0, %1"
    : "+m"(*addr), "=a"(result)
    : "1"(newval)
    : "cc");
    return result;
}

uint32_t compare_and_swap(volatile uint32_t* addr, uint32_t oldval, uint32_t newval) {
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
void spinlock_init(spinlock_t* lk) {
    lk->locked = 0;
}

void spinlock_lock(spinlock_t* lk) {
    while (test_and_set(&lk->locked, 1) != 0)
        asm volatile("pause");
}

void spinlock_unlock(spinlock_t* lk) {
    test_and_set(&lk->locked, 0);
}

/************* ticketlock *************/
void ticketlock_init(ticketlock_t* lk) {
    lk->ticket = 0;
    lk->turn = 0;
}

void ticketlock_lock(ticketlock_t* lk) {
    int myturn = fetch_and_add(&lk->ticket);
    while (myturn != lk->turn);
}

void ticketlock_unlock(ticketlock_t* lk) {
    ++lk->turn;
}

/************* mcslock *************/

void mcs_lock_init(mcslock_t* lk) {
    lk->tail = NULL;
}

