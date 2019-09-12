//
// Created by SNAKE on 2019-09-10.
//

#include "sort_impl.h"

typedef vector<int> ar;

template<class Comparable>
using sortFunc = void (*)(vector<Comparable> &a);

bool check(ar &v) {
  int size = v.size();
  for (int j = 0; j < size - 2; ++j) {
    if (v[j] > v[j + 1])
      return false;
  }
  return true;
}

void randv(ar &v, int size) {
  for (int i = 0; i < size; ++i)
    v[i] = rand() % (size << 1);
}

template<class Comparable>
void testSort(sortFunc<Comparable> f, int size, int iter, string msg) {
  ar v(size);
  for (int i = 0; i < iter; ++i) {
    randv(v, size);
    f(v);
    if (!check(v)) {
      cout << msg << " sort test failed.\n";
      return;
    }
  }
  cout << msg << " sort test pass.\n";
}

template<class Comparable>
void auto_test() {
  map<sortFunc<Comparable>, string> f = {
    {insertionSort, "insertionSort"},
    {selectionSort, "selectionSort"},
    {bubbleSort,    "bubbleSort"},
    {shellSort,     "shellSort"}
  };

  for (auto &d:f)
    testSort(d.first, 100, 10, d.second);
}

int main() {
  auto_test<int>();
}