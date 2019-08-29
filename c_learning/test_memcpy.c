//
// Created by SNAKE on 2019-08-29.
//
#include "memcpy.h"

#define COUNT 2000
#define SENDCORE 2

#define NANO 1000000000
#define MILI 1000000
#define KILO 1000
#define ALIGNMENT 1024
#define PGSIZE 4096


static void timespec_sub(struct timespec* t1, struct timespec* t2) {
    assert(t1->tv_nsec >= 0 && t1->tv_nsec < NANO);
    assert(t2->tv_nsec >= 0 && t2->tv_nsec < NANO);

    t1->tv_sec -= t2->tv_sec;
    t1->tv_nsec -= t2->tv_nsec;

    if (t1->tv_nsec >= NANO) {
        ++t1->tv_sec;
        t1->tv_nsec -= NANO;
    } else if (t1->tv_nsec < 0) {
        --t1->tv_sec;
        t1->tv_nsec += NANO;
    }
}

void test_memcpy(enum MC_CHOICE c) {
    int rc;

    char* src = NULL, * dst = NULL;
    char* psrc = NULL, * pdst = NULL;

    struct timespec begin, end;

    uint64_t size = 1lu << 20u;
    int temp = 0;
    int count = 0;

    unsigned long long timec = 0;
//    if (SENDCORE) {
//        cpu_set_t cpu_set;
//        CPU_ZERO(&cpu_set);
//
//    }
    printf("TEST %s:\n", mcstr[c]);

    if (posix_memalign((void**) &src, ALIGNMENT, 0x60000000)) {
        perror("posix_memalign src error\n");
        return;
    }
    if (posix_memalign((void**) &dst, ALIGNMENT, 0x60000000)) {
        free(src);
        perror("posix_memalign dst error\n");
        return;
    }

    for (int k = 4; k < 8; ++k) {
        count = 0;

        rc = clock_gettime(CLOCK_MONOTONIC, &begin);
        for (int i = 0; i < COUNT; ++i, ++count) {
            temp = size >> 11;
            psrc = src;
            pdst = dst;
#if 0
            mc[c](pdst,psrc,size);
#else
            for (int j = 0; j < temp; ++j) {
                mc[c](pdst, psrc, PGSIZE);
                pdst += PGSIZE;
                psrc += PGSIZE;
            }
#endif
        }
        rc = clock_gettime(CLOCK_MONOTONIC, &end);

//        printf("\tcopy data by 4KB total count is %d\n", count / COUNT);

        timespec_sub(&end, &begin);
        timec = end.tv_sec * MILI + end.tv_nsec / KILO;
        printf("\tCLOCK_MONOTONIC report: %.3fus for copy %d times %dKB\n",
               1.0 * timec / COUNT, COUNT, size >> 10);
        size <<= 1;
    }
    free(src);
    free(dst);
}

int main() {
    for (int i = 0; i < C; ++i)
        test_memcpy(i);
}