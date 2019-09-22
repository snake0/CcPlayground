//
// Created by SNAKE on 9/21/19.
//

#ifndef SYSBENCH_SB_TEST_H
#define SYSBENCH_SB_TEST_H

#include "sb_list.h"
#include "sb_option.h"
#include <stdint.h>

typedef int sb_builtin_cmd_func_t(void);
typedef int sb_custom_cmd_func_t(int);

/* Test operations definition */

typedef struct {
  uint32_t threads_running;     /* Number of active threads */

  double time_interval;       /* Time elapsed since the last report */
  double time_total;          /* Time elapsed since the benchmark start */

  double latency_pct;         /* Latency percentile */

  double latency_min;         /* Minimum latency (cumulative reports only) */
  double latency_max;         /* Maximum latency (cumulative reports only) */
  double latency_avg;         /* Average latency (cumulative reports only) */
  double latency_sum;         /* Sum latency (cumulative reports only) */

  uint64_t events;              /* Number of executed events */
  uint64_t reads;               /* Number of read operations */
  uint64_t writes;              /* Number of write operations */
  uint64_t other;               /* Number of other operations */
  uint64_t errors;              /* Number of ignored errors */
  uint64_t reconnects;          /* Number of reconnects to server */

  uint64_t bytes_read;          /* Bytes read */
  uint64_t bytes_written;       /* Bytes written */

  uint64_t queue_length;        /* Event queue length (tx_rate-only) */
  uint64_t concurrency;         /* Number of in-flight events (tx_rate-only) */
} sb_stat_t;

typedef int sb_op_init(void);
typedef int sb_op_prepare(void);
typedef int sb_op_thread_init(int);
typedef int sb_op_thread_run(int);
typedef void sb_op_print_mode(void);
typedef void sb_op_report(sb_stat_t *);
typedef int sb_op_thread_done(int);
typedef int sb_op_cleanup(void);
typedef int sb_op_done(void);

/* Test commands structure definitions */

typedef struct {
  sb_builtin_cmd_func_t *help;  /* print help */
  sb_builtin_cmd_func_t *prepare; /* prepare for the test */
  sb_builtin_cmd_func_t *run;   /* run the test */
  sb_builtin_cmd_func_t *cleanup; /* cleanup the test database, files, etc. */
} sb_builtin_cmds_t;

/* Test operations structure definition */

typedef struct {
  sb_op_init *init;            /* initialization function */
  sb_op_prepare *prepare;         /* called after timers start,  but
                                             before thread execution */
  sb_op_thread_init *thread_init;     /* thread initialization
                                             (called when each thread starts) */
  sb_op_print_mode *print_mode;      /* print mode function */
  sb_op_report *report_intermediate; /* intermediate reports handler */
  sb_op_report *report_cumulative;   /* cumulative reports handler */
  sb_op_thread_run *thread_run;      /* main thread loop */
  sb_op_thread_done *thread_done;     /* thread finalize function */
  sb_op_cleanup *cleanup;         /* called after exit from thread,
                                             but before timers stop */
  sb_op_done *done;            /* finalize function */
} sb_operations_t;

/* Test structure definition */

typedef struct sb_test {
  const char *sname;
  const char *lname;
  sb_operations_t ops;
  sb_builtin_cmds_t builtin_cmds;
  sb_list_t options;

  sb_list_item_t listitem;
} sb_test_t;

extern sb_list_t tests;

void sb_test_init(void);


#endif //SYSBENCH_SB_TEST_H
