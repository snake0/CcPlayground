#include "sb_option.h"
#include "sb_test.h"
#include <stdio.h>
#include "sb_util.h"
#include "sysbench.h"



sb_option_t *sb_option_get_entry(const char *name) {
  sb_list_for_each (options) {
    sb_option_t *opt = sb_list_entry(pos, sb_option_t);
    if (!strcmp(opt->name, name))
      return opt;
  }
  return NULL;
}

char *sb_option_get_value(const char *name) {
  sb_option_t *opt = sb_option_get_entry(name);
  return !opt ? NULL : opt->value;
}

int sb_option_set_value(const char *name, char *value) {
  sb_option_t *opt = sb_option_get_entry(name);

  if (opt != NULL) {
    opt->value = value;
    return SB_OK;
  }
  return SB_OPTION_UNKNOWN;
}

void sb_option_init(void) {
  sb_list_init(options);

  int i = 0;
  for (; default_options[i].type != SB_ARG_TYPE_NULL; ++i)
    sb_list_add(options, default_options[i]);
}

int sb_option_parse(int argc, char **argv) {
  for (int i = 1; i < argc; ++i) {
    if (!strncmp("--", argv[i], 2)) { // general option
      char *assign = strchr(argv[i], '=');
      if (!assign)
        return SB_OPTION_SYNTAX;

      *assign = '\0';
      if (sb_option_set_value(argv[i] + 2, assign + 1))
        return SB_OPTION_UNKNOWN;

    } else { // test command
      sb_test_t *test = sb_test_get_entry(argv[i]);
      if (!test)
        return SB_TEST_UNKNOWN;
      current_test = test;
    }
  }
  return SB_OK;
}