//
// Created by SNAKE on 9/21/19.
//

#ifndef SYSBENCH_SYSBENCH_H
#define SYSBENCH_SYSBENCH_H

#include "sb_option.h"
#include "sb_test.h"
#include "sb_util.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

struct {
  int threads;
  const char *testname, *cmdname;
  sb_test_t *test;
} sb_globals;

#endif //SYSBENCH_SYSBENCH_H
