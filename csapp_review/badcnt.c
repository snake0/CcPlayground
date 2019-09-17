/* 
 * badcnt.c - An improperly synchronized counter program 
 */
/* $begin badcnt */
/* WARNING: This code is buggy! */
#include "csapp.hxx"

void *thread(void *vargp);  /* Thread routine prototype */

/* Global shared variable */
atomic_long atomicLong = 0;
volatile long cnt = 0; /* Counter */
sem_t *mutex; /* Semaphore */

int main(int argc, char **argv) {
  long niters;
  pthread_t tid1, tid2;

  /* Check input argument */
  if (argc != 2) {
    printf("usage: %s <niters>\n", argv[0]);
    exit(0);
  }
  niters = atoi(argv[1]);

  /* on OS X */
  mutex = sem_open("/mysem", O_CREAT, S_IRUSR | S_IWUSR, 1);

  /* Create threads and wait for them to finish */
  Pthread_create(&tid1, NULL, thread, &niters);
  Pthread_create(&tid2, NULL, thread, &niters);
  Pthread_join(tid1, NULL);
  Pthread_join(tid2, NULL);

  /* Check result */
  if (atomicLong != (2 * niters))
    printf("BOOM! cnt=%ld\n", cnt);
  else
    printf("OK cnt=%ld\n", atomicLong);

  sem_close(mutex);
  sem_unlink("/mysem");
  exit(0);
}

/* Thread routine */
void *thread(void *vargp) {
  long i, niters = *((long *) vargp);

  for (i = 0; i < niters; i++) {//line:conc:badcnt:beginloop
//    P(mutex);
    ++atomicLong;                   //line:conc:badcnt:endloop
//    V(mutex);
  }
  return NULL;
}
/* $end badcnt */

