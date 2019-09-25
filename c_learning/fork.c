//
// Created by SNAKE on 9/25/19.
//

#include "include_for_c.h"

static int s = 0;

int main() {
  int *p = (int *) malloc(sizeof(int));
  pid_t pid = fork();
  if (pid == 0) {
    *p = 100;
    s = 1;
    printf("child %d, %d\n", *p, s);
    exit(0);
  }
  wait(NULL);
  printf("parent %d, %d\n", *p, s);
  exit(0);
}