#ifndef SB_UTILS_H
#define SB_UTILS_H

enum err {
  SB_OK,
  SB_OPTION_SYNTAX,
  SB_OPTION_UNKNOWN,
  SB_TEST_UNKNOWN,
  SB_MAX
};

char *errmsg[] = {
  [SB_OPTION_SYNTAX]="Invalid option syntax\n",
  [SB_OPTION_UNKNOWN]="Unknown option\n",
  [SB_TEST_UNKNOWN]="Unknown test\n",
};


#endif // SB_UTILS_H