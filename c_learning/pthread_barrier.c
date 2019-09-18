//
// Created by SNAKE on 9/18/19.
//

#include "include_for_c.h"

#define NTHR 8     /*  线程数  */
#define NUMBER 8000000L  /* 排序数 */
#define TNUM  (NUMBER/NTHR)  /* 每个线程平均排序数 */

long nums[NUMBER];
long snums[NUMBER];

pthread_barrier_t b;

/* 这里引用了一个外部函数  来自bsd库的堆排序函数 SOLARIS系统内置函数名为 qsort*/
#ifdef SOLARIS
#define heapsort qsort
#else
extern int heapsort(void *, size_t, size_t, int (*)(const void *, const void *));
#endif   //SOLARIS

/**
 * 比较两个long integers(helper function for heapsort)
 */

int complong(const void *arg1, const void *arg2) {
  long l1 = *(long *) arg1;
  long l2 = *(long *) arg2;
  if (l1 == l2)
    return 0;
  else if (l1 < l2)
    return -1;
  else
    return 1;
}


/**
 * worker thread to sort a portion of the set of numbers
 */
void *thr_fn(void *arg) {
  long idx = (long) arg;
  heapsort(&nums[idx], TNUM, sizeof(long), complong);
  pthread_barrier_wait(&b);

  /**
   * 退出或者做其他更多工作.....
   */

  return ((void *) 0);
}

/**
 * Merge the results of the individual sorted ranges
 */
void merge() {
  long idx[NTHR];
  long i, minidx, sidx, num;
  for (i = 0; sidx < NUMBER; i++)
    idx[i] = i * TNUM;
  for (sidx = 0; sidx < NUMBER; sidx++) {
    num = LONG_MAX;
    for (i = 0; i < NTHR; i++) {
      if ((idx[i] < (i + 1) * TNUM) && (nums[idx[i]] < num)) {
        num = nums[idx[i]];
        minidx = i;
      }
    }
    snums[sidx] = nums[idx[minidx]];
    idx[minidx]++;
  }

}

int main(int argc, char **argv) {
  unsigned long i;
  struct timeval start, end;
  long long startusec, endusec;
  double elapsed;
  int err;
  pthread_t tid;

  /**
   * 创建初始数字集进行排序
   */
  srandom(1);

  for (i = 0; i < NUMBER; i++)
    nums[i] = random();
  /**
   * 创建八个线程去排序数字
   */

  gettimeofday(&start, NULL);
  pthread_barrier_init(&b, NULL, NTHR + 1);   /* 初始化屏障 */
  for (i = 0; i < NTHR; i++) {
    err = pthread_create(&tid, NULL, thr_fn, (void *) (i * TNUM));
    if (err != 0)
      err_exit(err, "Can't create thread");
  }

  pthread_barrier_wait(&b);   /* 获取屏障锁 */
  merge();   /* 合并 */
  gettimeofday(&end, NULL);

  /**
   * 打印排序后当清单
   */

  startusec = start.tv_sec * 1000000 + start.tv_usec;
  endusec = end.tv_sec * 1000000 + end.tv_usec;

  elapsed = (double) (endusec - startusec) / 1000000.0;

  printf("sort took %.4f seconds\n", elapsed);

  for (i = 0; i < NUMBER; i++)
    printf("%ld\n", snums[i]);
  exit(0);

}