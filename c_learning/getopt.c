//
// Created by SNAKE on 10/2/19.
//

#include "include_for_c.h"

typedef struct _sb_option {
  const char *name;
  const char *desc;
  union val {
    long intval;
    char *strval;
  };
} sb_option;

enum SB_OPTION {
  THREADS,
  EVENTS,
  OPT_END
};
extern char *test_name;

sb_option general_options[OPT_END] = {
  [THREADS] = {"threads", "number of threads to use", {"1"}},
  [EVENTS] = {"events", "number of events to execute", {"1000"}}
};

int main(int argc, char *argv[]) {
  int opt;
  int option_index = 0;
  char *optstring = "a:b:c:d";
  static struct option long_options[] = {
    {"reqarg", required_argument, NULL, 'r'},
    {"noarg",  no_argument,       NULL, 'n'},
    {"optarg", optional_argument, NULL, 'o'},
    {0, 0, 0,                           0}
  };

  while ((opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1) {
    printf("opt = %c\n", opt);
    printf("optarg = %s\n", optarg);
    printf("optind = %d\n", optind);
//    printf("optopt = %d\n", optopt);
    printf("argv[optind - 1] = %s\n", argv[optind - 1]);
    printf("option_index = %d\n", option_index);
  }

  return 0;
}