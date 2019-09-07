//
// Created by snake0 on 2019/9/6.
//
#include <stdio.h>
int main() {
    auto int a = 1;
    register int b = 2;
    volatile int c = 3;
    printf("auto %d, register %d, volatile %d\n", a,b,c);
}