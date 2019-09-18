//
// Created by SNAKE on 9/18/19.
//

#include <iostream>
#include <mutex>
#include <string>
#include <thread>

thread_local unsigned int rage = 1;
std::mutex cout_mutex;

void increase_rage(const std::string &thread_name) {
  ++rage; // 在锁外修改 OK ；这是线程局域变量
  std::lock_guard<std::mutex> lock(cout_mutex);
  std::cout << "Rage counter for " << thread_name << ": " << rage << '\n';
}

void test() {
  thread_local int i = 0;
  printf("id=%ld, n=%d\n", std::this_thread::get_id(), i);
  i++;
}

void test2() {
  test();
  test();
}

int main() {
  std::thread a(increase_rage, "a"), b(increase_rage, "b");

  {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Rage counter for main: " << rage << '\n';
  }

  a.join();
  b.join();

  std::thread t1(test);
  std::thread t2(test);
  t1.join();
  t2.join();

  std::thread t3(test2);
  t3.join();

  return 0;
}