cmake_minimum_required(VERSION 3.14)
project(leetcode)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

#cpp

add_executable(const_cast cpp_learning/const_cast.cc ds_and_al/test_ds_and_al.cc)
add_executable(constexpr cpp_learning/constexpr.cc)
add_executable(dynamic_cast cpp_learning/dynamic_cast.cc)
add_executable(forward cpp_learning/forward.cc)
add_executable(future cpp_learning/future.cc)
add_executable(keywords cpp_learning/keywords.cc)
add_executable(mutex cpp_learning/mutex.cc)
add_executable(numeric_limits cpp_learning/numeric_limits.cc)
add_executable(reinterpret_cast cpp_learning/reinterpret_cast.cc)
add_executable(remove_file cpp_learning/remove_file.cc)
add_executable(shared_ptr cpp_learning/shared_ptr.cc)
add_executable(static_cast cpp_learning/static_cast.cc)
add_executable(unique_ptr cpp_learning/unique_ptr.cc)
add_executable(noexcept cpp_learning/noexcept.cc)
add_executable(test_dsal ds_and_al/test_ds_and_al.cc)
add_executable(leetcode_in_cpp leetcode/solution.cc)
add_executable(cpp_volatile cpp_learning/volatile.cpp)

#c
add_executable(leetcode_in_c c_learning/lock.c leetcode/solution.c)
add_executable(test_memcpy c_learning/test_memcpy.c)
add_executable(test_lock c_learning/lock.c c_learning/test_lock.c)
add_executable(c_volatile c_learning/volatile.c)
add_executable(threads c_learning/threads.c)

#csapp
add_executable(badcnt csapp_review/badcnt.c)