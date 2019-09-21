cmake_minimum_required(VERSION 3.14)
project(sysbench C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(tests)

add_executable(sysbench
        tests/sb_cpu.c
        tests/sb_cpu.h
        sb_list.h
        sb_option.c
        sb_option.h
        sb_test.c
        sb_test.h
        sb_thread.c
        sb_thread.h
        sb_timer.c
        sb_timer.h
        sb_utils.h
        sysbench.c)
