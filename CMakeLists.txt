cmake_minimum_required(VERSION 3.14)
project(leetcode)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

#cpp

add_executable(const_cast cpp_learning/const_cast.cc ds_and_al/test_ds.cc)
add_executable(constexpr cpp_learning/constexpr.cc)
add_executable(dynamic_cast cpp_learning/dynamic_cast.cc)
add_executable(forward cpp_learning/forward.cc)
add_executable(future cpp_learning/future.cc)
add_executable(keywords cpp_learning/keywords.cc)
add_executable(mutex cpp_learning/mutex.cc)
add_executable(numeric_limits cpp_learning/numeric_limits.cc)
add_executable(reinterpret_cast cpp_learning/reinterpret_cast.cc)
add_executable(remove_file cpp_learning/remove_file.cc)
add_executable(static_cast cpp_learning/static_cast.cc)
add_executable(smart_ptr cpp_learning/smart_ptr.cc)
add_executable(noexcept cpp_learning/noexcept.cc)
add_executable(test_dsal ds_and_al/test_ds.cc)
add_executable(leetcode_in_cpp leetcode/solution.cc)
add_executable(cpp_volatile cpp_learning/volatile.cpp)
add_executable(thread_local cpp_learning/thread_local.cc)

#c
add_executable(leetcode_in_c leetcode/solution.c)
add_executable(test_memcpy c_learning/test_memcpy.c)
add_executable(test_lock c_learning/lock.c c_learning/test_lock.c c_learning/dup.c)
add_executable(c_volatile c_learning/volatile.c)
add_executable(barrier c_learning/pthread_barrier.c c_learning/lock.c)
target_link_libraries(barrier pthread)
add_executable(core c_learning/which_core.c)
add_executable(dup c_learning/dup.c)
add_executable(fork csapp_review/fork.c)
add_executable(waitpid csapp_review/waitpid.c)
add_executable(getopt c_learning/getopt.c)

#csapp
add_executable(badcnt csapp_review/badcnt.c)