//
// Created by SNAKE0's MACBOOK PRO on 2019/10/11.
//

__attribute__((always_inline)) inline static void
ck_pr_barrier(void) {
  __asm__ __volatile__("":: : "memory");
}

int main() {
  int a = 1, b = 3;
  b = 111;
  __asm__ __volatile__("":: : "memory");
  b = a;
  return b;
}