#include "include_for_c.h"

char *p;

char *f() {
  char **a = (char **) malloc(sizeof(char **));
  *a = "i am fat";
  return *a;
}

int main() {
  p = f();
  printf("%d", strncmp(p, "i am faa", strlen("i am fat")));
}