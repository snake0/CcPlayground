//
// Created by SNAKE on 9/21/19.
//

#include "sb_cpu.h"
#include "sb_test.h"
#include "sb_option.h"
#include "sb_list.h"
#include "sysbench.h"

/* CPU test arguments */
static sb_option_t cpu_args[] =
  {
    SB_OPT("cpu-max-prime", "upper limit for primes generator", "10000", INT),

    SB_OPT_END
  };
/* CPU test operations */
static int cpu_init(void);
static void cpu_print_mode(void);
static void cpu_report_cumulative(sb_stat_t *);
static int cpu_done(void);

sb_test_t cpu_test =
  {
    .sname = "cpu",
    .lname = "CPU performance test",
    .ops = {
      .init = cpu_init,
      .print_mode = cpu_print_mode,
      .report_cumulative = cpu_report_cumulative,
      .done = cpu_done
    },
    .args = cpu_args
  };

void register_cpu(void) {
  sb_list_add(tests, cpu_test);
}


int cpu_init(void) {

}

void cpu_print_mode(void) {

}

void cpu_report_cumulative(sb_stat_t *stat) {

}

int cpu_done(void) {

}
