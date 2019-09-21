cmake_minimum_required(VERSION 3.14)
project(sysbench)

set(CMAKE_C_STANDARD 11)

add_executable(sysbench sysbench.c sb_option.c)
