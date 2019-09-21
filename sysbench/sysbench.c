//
// Created by SNAKE on 9/21/19.
//

#include "sb_option.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  sb_option_init();
  for (int i = 0; i < argc; ++i)
    printf("%s\n", argv[i]);
}