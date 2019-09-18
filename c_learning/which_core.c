//
// Created by SNAKE on 9/18/19.
//

#include "include_for_c.h"

atomic_int cnt = 0;
#define THREADS 4

clock_t b, e;

pthread_t threads[THREADS];

void *thread(void *arg) {
  while (cnt < 50000000)
    ++cnt;
  return (void *) 0;
}

int main() {
  b = clock();
  for (int i = 0; i < THREADS; ++i) {
    pthread_create(&threads[i], NULL, thread, NULL);
  }
  for (int i = 0; i < THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }
  e = clock();
  double time = (double) (e - b) / CLOCKS_PER_SEC;
  printf("%f", time);
}