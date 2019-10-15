//
// Created by SNAKE0's MACBOOK PRO on 2019/10/11.
//

__attribute__((always_inline)) inline static void
ck_pr_barrier(void) {
  __asm__ __volatile__("":: : "memory");
}

#include "include_for_c.h"

int main() {
  int count = 1;
  int child;

  // child = vfork( );

  printf("Before create son, the father's count is : %d\n", count);

  if ((child = vfork()) < 0) {
    perror("fork error : ");
  } else if (child == 0)     //  fork return 0 in the child process because child can get hid PID by getpid( )
  {
    printf("This is son, his count is: %d (%p). and his pid is: %d\n", ++count, &count, getpid());

  } else                    //  the PID of the child process is returned in the parent’s thread of execution
  {
    printf("After son, This is father, his count is: %d (%p), his pid is: %d\n", count, &count, getpid());
    usleep(200);
  }

  return EXIT_SUCCESS;
}