//
// Created by SNAKE on 9/25/19.
//

#include "include_for_c.h"

static char s[] = "abcd";

int main() {
  int *p = (int *) malloc(sizeof(int));
  pid_t pid = fork();
  if (pid == 0) {
    *p = 100;
    s[1] = 'z';
    printf("child %p, %s\n", main, s);
    exit(0);
  }
  wait(NULL);
  printf("parent %p, %s\n", main, s);
  exit(0);
}