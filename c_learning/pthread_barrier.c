//
// Created by SNAKE on 9/18/19.
//

#include "include_for_c.h"
#include "lock.h"

pthread_barrier_t barrier;

volatile int count = 0;
spinlock_t spinlock;

void *thread(void *arg) {
  spinlock_lock(&spinlock);
  ++count;
  spinlock_unlock(&spinlock);
  pthread_barrier_wait(&barrier);
  printf("%d ",count);

}

int main(int argc, char *argv[]) {
  int thread_num = -1;

  if (argc == 2) {
    thread_num = atoi(argv[1]);
  } else {
    printf("usage: ddd [thread_num]\n");
    return 1;
  }

  spinlock_init(&spinlock);
  pthread_barrier_init(&barrier, 0, thread_num);
  pthread_t *pids = (pthread_t *) malloc(sizeof(pthread_t) * thread_num);
  for (int i = 0; i < thread_num; ++i) {
    pthread_create(&pids[i], 0, thread, 0);
  }
//  pthread_barrier_wait(&barrier);

  printf("create done\n");

  for (int i = 0; i < thread_num; ++i) {
    pthread_join(pids[i], 0);
  }

}