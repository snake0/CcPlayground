#include "lock.h"
#include "memcpy.h"

void test(int k) {
  char* p = (char*) malloc(123);
  p[0] = '1';
  p[1] = '2';
  p[2] = '3';
  p[3] = '4';
  p[4] = '5';
  mc[k](p + 2, p, 5);
  prstr(p, 5);
  prstr(p + 2, 5);
  free(p);
}

int main() {
  for (int i = 0; i < 4; ++i) {
    test(i);
  }
}