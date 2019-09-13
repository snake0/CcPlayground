//
// Created by SNAKE on 2019-09-10.
//

#include "Sort.h"
#include "List.h"
#include "Vector.h"
#include "BinaryHeap.h"
#include "BinarySearchTree.h"

typedef vector<int> ar;

template<class Comparable, class Comparator=less<Comparable>>
using sortFunc = void (*)(vector<Comparable> &a, Comparator lessThan);

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
    f(v, less<int>());
    if (!check(v)) {
      cout << msg << " test failed.\n";
      return;
    }
  }
  cout << msg << " test pass.\n";
}

typedef struct __binding {
  int key;
  int value;
} binding;

template<class Comparable, class Comparator=less<Comparable>>
void auto_test() {
  static map<sortFunc<Comparable, Comparator>, string> f = {
    {insertionSort, "insertionSort"},
    {selectionSort, "selectionSort"},
    {bubbleSort,    "bubbleSort"},
    {shellSort,     "shellSort"},
    {heapSort,      "heapSort"},
    {mergeSort,     "mergeSort"},
    {quickSort,     "quickSort"},
  };

  for (auto &d:f)
    testSort(d.first, 100, 10, d.second);
}

bool lessThanBinding(binding &l, binding &r) {
  return l.key < r.key;
}

int main() {
//  auto_test<int>();
  vector<binding> v = {{2, 122},
                       {0, 2221},
                       {1, 3334}};
  cout << (v.end() > v.end());
  bubbleSort(v, lessThanBinding);
}