//
// Created by SNAKE on 9/21/19.
//

#ifndef SYSBENCH_SYSBENCH_H
#define SYSBENCH_SYSBENCH_H

#include "sb_option.h"
#include "sb_test.h"
#include <stdio.h>

extern sb_list_t tests;
extern sb_list_t options;

extern sb_test_t* current_test;
extern sb_option_t default_options[];

#endif //SYSBENCH_SYSBENCH_H
