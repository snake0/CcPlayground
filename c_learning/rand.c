//
// Created by SNAKE0's MACBOOK PRO on 2019/10/11.
//

#include "include_for_c.h"

#define THREADS 10
pthread_t threads[THREADS];
pthread_mutex_t mutex;

struct xorshift128p_state {
  uint64_t a, b;
};

/* The state must be seeded so that it is not all zero */
uint64_t xorshift128p(struct xorshift128p_state *state) {
  uint64_t t = state->a;
  uint64_t const s = state->b;
  state->a = s;
  t ^= t << 23;        // a
  t ^= t >> 17;        // b
  t ^= s ^ (s >> 26);    // c
  state->b = t;
  return t + s;
}

void *thread(void *arg) {
  pthread_mutex_lock(&mutex);
  long id = (long) arg;
//    printf("id: %ld\n", id);

  struct xorshift128p_state s = {id, 10000 - id};
  for (int i = 0; i < 6; ++i) {
    printf("%llu ", xorshift128p(&s) % 10);
  }
  printf("\n");
  pthread_mutex_unlock(&mutex);
  return (void *) 0;
}

int main() {
  pthread_mutex_init(&mutex, 0);
  for (int i = 0; i < THREADS; ++i) {
    pthread_create(&threads[i], NULL, thread, (void *) i);
  }
  for (int i = 0; i < THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }
}