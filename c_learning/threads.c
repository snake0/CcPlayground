//
// Created by SNAKE on 2019-09-10.
//

#include "csapp.h"

#define _GNU_SOURCE

/*线程一*/
void thread_1(void) {
  int i = 0;
  for (i = 0; i <= 6; i++) {
    printf("This is a pthread_1.\n");
    if (i == 2)
      pthread_exit(0);                      //用pthread_exit()来调用线程的返回值，用来退出线程，但是退出线程所占用的资源不会随着线程的终止而得到释放
    sleep(1);
  }
}


/*线程二*/
void thread_2(void) {
  int i;
  for (i = 0; i < 3; i++)
    printf("This is a pthread_2.\n");
  pthread_exit(0);                              //用pthread_exit()来调用线程的返回值，用来退出线程，但是退出线程所占用的资源不会随着线程的终止而得到释放
}

struct s {
  int ss;
  long long d;
};

int main(void) {
  printf("%lu", offsetof(struct s, d));
}