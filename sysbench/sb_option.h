#ifndef SB_OPTION_H
#define SB_OPTION_H

#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "sb_list.h"

typedef enum {
  SB_ARG_TYPE_NULL,
  SB_ARG_TYPE_BOOL,
  SB_ARG_TYPE_INT,
  SB_ARG_TYPE_SIZE,
  SB_ARG_TYPE_DOUBLE,
  SB_ARG_TYPE_STRING,
  SB_ARG_TYPE_LIST,
  SB_ARG_TYPE_FILE,
  SB_ARG_TYPE_MAX
} sb_arg_type_t;

typedef struct {
  const char *name, *desc;
  char *value;
  sb_arg_type_t type;
  sb_list_item_t listitem;
} sb_option_t;

/* Helper option declaration macros */
#define SB_OPT(n, d, v, t)                   \
  { .name = (n),                             \
    .desc = (d),                             \
    .type = SB_ARG_TYPE_##t,                 \
    .value = (v) }

#define SB_OPT_END { .type = SB_ARG_TYPE_NULL }

extern sb_list_t general_options;
extern sb_option_t default_general_options[];

int sb_option_set_value(const char *name, char *value, sb_list_t opts);
static sb_option_t *sb_option_get_entry(const char *name, sb_list_t opts);
void sb_option_init(void);
int sb_option_parse(int argc, char **argv);

int sb_option_int(const char *name, sb_list_t opts);

void sb_option_print(void);
#endif // SB_OPTION_H