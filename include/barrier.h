//
// Created by SNAKE on 2019-08-28.
//
#ifndef _MCT_BARRIER_H_
#define _MCT_BARRIER_H_

#define barrier()       asm volatile("": : :"memory")

#ifdef CONFIG_SAME_CPU
#undef smp_mb()
#undef smp_rmb()
#undef smp_wmb()
#define smp_mb()        barrier()
#define smp_rmb()       barrier()
#define smp_wmb()       barrier()
#else /*ifdef CONFIG_SAME_CPU*/
#define mb()            asm volatile("mfence":::"memory")
#define rmb()           asm volatile("lfence":::"memory")
#define wmb()           asm volatile("sfence" ::: "memory")
#define smp_mb()        mb()
#define smp_rmb()       rmb()
#define smp_wmb()       wmb()
#endif /*CONFIG_SAME_CPU*/


#endif /*_MCC_BARRIER_H_*/