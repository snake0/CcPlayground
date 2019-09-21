//
// Created by SNAKE on 2019-09-10.
//

#include "Sort.h"
#include "List.h"
#include "Vector.h"
#include "BinaryHeap.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "clist.h"

//using namespace chrono;
//typedef vector<int> ar;
//
//template<class Comparable, class Comparator=less<Comparable>>
//using sortFunc = void (*)(vector<Comparable> &a, Comparator lessThan);
//
//bool check(ar &v) {
//  int size = v.size();
//  for (int j = 0; j < size - 2; ++j) {
//    if (v[j] > v[j + 1])
//      return false;
//  }
//  return true;
//}
//
//void randv(ar &v, int size) {
//  for (int i = 0; i < size; ++i)
//    v[i] = rand() % (size << 1);
//}
//
//template<class Comparable>
//void testSort(sortFunc<Comparable> f, int size, int iter, string msg) {
//  ar v(size);
//  for (int i = 0; i < iter; ++i) {
//    randv(v, size);
//    f(v, less<int>());
//    if (!check(v)) {
//      cout << msg << " test failed.\n";
//      return;
//    }
//  }
//  cout << msg << " test pass.\n";
//}
//
//typedef struct __binding {
//  int key;
//  int value;
//} binding;
//
//template<class Comparable, class Comparator=less<Comparable>>
//void auto_test() {
//  static map<sortFunc<Comparable, Comparator>, string> f = {
//    {insertionSort, "insertionSort"},
//    {selectionSort, "selectionSort"},
//    {bubbleSort,    "bubbleSort"},
//    {shellSort,     "shellSort"},
//    {heapSort,      "heapSort"},
//    {mergeSort,     "mergeSort"},
//    {quickSort,     "quickSort"},
//  };
//
//  for (auto &d:f) {
//    auto start = system_clock::now();
//    testSort(d.first, 1000, 100, d.second);
//    auto end = system_clock::now();
//    auto duration = duration_cast
//      <microseconds>(end - start);
//    cout << "花费了"
//         << double(duration.count()) * microseconds::period::num / microseconds::period::den
//         << "秒" << endl;
//  }
//}
//
//bool lessThanBinding(binding &l, binding &r) {
//  return l.key < r.key;
//}

int main() {
//  auto_test<int>();
//  vector<binding> v = {{2, 122},
//                       {0, 2221},
//                       {1, 3334}};
//  cout << (v.end() > v.end());
//  bubbleSort(v, lessThanBinding);
//  BinaryHeap<int> j{vector<int>{8,7, 6, 5, 4, 3, 2, 1}};
////  cout << boolalpha << j.print() << endl;
//  j.print();
//cout << (1<<31);

}