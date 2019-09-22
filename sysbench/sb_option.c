#include "sb_option.h"
#include "sb_test.h"
#include "sb_util.h"
#include "sysbench.h"

static sb_list_t general_options;

static sb_option_t default_general_options[] = {
  SB_OPT("threads", "number of threads to use", "1", INT),
  SB_OPT("events", "limit for total number of events", "0", INT),
  SB_OPT("validate", "perform validation checks where possible", "off", BOOL),
  SB_OPT("help", "print help and exit", "off", BOOL),

  SB_OPT_END
};

static sb_option_t *sb_option_get_entry(const char *name, sb_list_t opts) {
  sb_list_for_each (opts) {
    sb_option_t *opt = sb_list_entry(sb_option_t);
    if (!strcmp(opt->name, name))
      return opt;
  }
  return NULL;
}

int sb_option_set_value(const char *name, char *value, sb_list_t opts) {
  sb_option_t *opt = sb_option_get_entry(name, opts);

  if (opt != NULL) {
    opt->value = value;
    return SB_OK;
  }
  return SB_OPTION_UNKNOWN;
}

/* init general options with default value */
void sb_option_init(void) {
  sb_list_init(general_options);

  int i = 0;
  for (; default_general_options[i].type != SB_ARG_TYPE_NULL; ++i)
    sb_list_add(general_options, default_general_options[i]);
}

/* parse option like '--xxxxx' and set the option */
static int parse_option(char *arg, sb_list_t opts) {
  char *assign = strchr(arg, '=');
  if (!assign)
    return SB_OPTION_SYNTAX;

  *assign = '\0';
  if (sb_option_set_value(arg + 2, assign + 1, opts))
    return SB_OPTION_UNKNOWN;
  return SB_OK;
}

/* parse specific tests arguments */
static int parse_test_option(int i, int argc, char **argv) {
  int r;

  sb_list_for_each(tests) {
    sb_test_t *test = sb_list_entry(sb_test_t);

    if (!strcmp(argv[i], test->sname)) {
      sb_globals.test = test;
      sb_globals.testname = test->sname;

      for (; i < argc; ++i) {
        if (!strncmp("--", argv[i], 2)) {
          if ((r = parse_option(argv[i], test->options)))
            return r;
        } else {
          sb_globals.cmdname = argv[i];
          break;
        }
      }
    }
  }

  return SB_OK;
}

int sb_option_parse(int argc, char **argv) {
  int r;

  for (int i = 1; i < argc; ++i) {
    // general option
    if (!strncmp("--", argv[i], 2)) {
      if ((r = parse_option(argv[i], general_options)))
        return r;
    } else {
      if ((r = parse_test_option(i, argc, argv)))
        return r;
      break;
    }
  }
  return SB_OK;
}


int sb_option_int(const char *name, sb_list_t opts) {
  sb_option_t *opt = sb_option_get_entry(name, opts);
  if (!opt)
    return SB_OPTION_UNKNOWN;
  if (opt->type != SB_ARG_TYPE_INT)
    return SB_OPTION_TYPE;

  int ret = (int) strtol(opt->value, NULL, 10);
  if (errno)
    return SB_OPTION_TYPE;
  return ret;
}

void sb_option_print(void) {
  {
    printf("Running sysbench with general options:\n");
    sb_list_for_each(general_options) {
      sb_option_t *opt = sb_list_entry(sb_option_t);
      printf("  %-20s: %4s\n", opt->name, opt->value);
    }
  }
  {
    printf("%s test options: \n", sb_globals.testname);
    sb_list_for_each(sb_globals.test->options) {
      sb_option_t *opt = sb_list_entry(sb_option_t);
      printf("  %-20s: %4s\n", opt->name, opt->value);
    }
  }
}