//
// Created by SNAKE on 2019-09-02.
//

#include "csapp.h"

int main() {
    for (int i = 0; i < 2; ++i) {
        Fork();
        printf("%d ", i);
    }
}