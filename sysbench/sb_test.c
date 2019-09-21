//
// Created by SNAKE on 9/21/19.
//
#include "sysbench.h"
#include "sb_test.h"
#include "sb_cpu.h"

sb_list_t tests;

void sb_test_init(void) {
  register_cpu();
}

sb_test_t *sb_test_get_entry(const char *name) {
  sb_list_for_each(tests) {
    sb_test_t *test = sb_list_entry(sb_test_t);
    if (!strcmp(test->sname, name)) {
      return test;
    }
  }
  return NULL;
}
