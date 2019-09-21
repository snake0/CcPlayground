#ifndef SB_UTILS_H
#define SB_UTILS_H

enum err {
  SB_OK,
  SB_OPTION_SYNTAX,
  SB_OPTION_UNKNOWN,
  SB_TEST_UNKNOWN,
  SB_OPTION_TYPE,
  SB_MAX
};

static char *errmsg[] = {
  [SB_OPTION_SYNTAX]="Invalid option syntax",
  [SB_OPTION_UNKNOWN]="Unknown option",
  [SB_TEST_UNKNOWN]="Unknown test",
  [SB_OPTION_TYPE]="Option type error",
};

#define ASSERT(f) do { \
  int r = (f); \
  if (r) printf("SYSBENCH: %s\n",errmsg[r]);\
} while(0)


#endif // SB_UTILS_H