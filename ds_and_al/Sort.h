//
// Created by SNAKE on 2019-09-10.
//

#ifndef LEETCODE_SORT_H
#define LEETCODE_SORT_H

#include "include_for_cc.h"

template<typename Comparable, class Comparator=less<Comparable>>
void insertionSort(vector<Comparable> &a, Comparator lessThan = Comparator()) {
  int size = a.size();
  for (int p = 1; p < size; ++p) {
    Comparable tmp = std::move(a[p]);
    int j = p;
    for (; j && lessThan(tmp, a[j - 1]); --j)
      a[j] = std::move(a[j - 1]);
    a[j] = std::move(tmp);
  }
}

template<typename Comparable, class Comparator=less<Comparable>>
void selectionSort(vector<Comparable> &a, Comparator lessThan = Comparator()) {
  int size = a.size();
  for (int p = 0; p < size - 1; ++p) {
    int minIndex = p;
    for (int j = p + 1; j < size; ++j) {
      if (lessThan(a[j], a[minIndex])) {
        minIndex = j;
      }
    }
    std::swap(a[p], a[minIndex]);
  }
}

template<typename Comparable, class Comparator=less<Comparable>>
void bubbleSort(vector<Comparable> &a, Comparator lessThan = Comparator()) {
  int size = a.size();
  for (int p = size - 2; p + 1; --p) {
    for (int j = p + 1; j < size; ++j) {
      if (lessThan(a[j], a[j - 1])) {
        std::swap(a[j], a[j - 1]);
      }
    }
  }
}

template<typename Comparable, class Comparator=less<Comparable>>
void shellSort(vector<Comparable> &a, Comparator lessThan = Comparator()) {
  int size = a.size();
  for (int gap = size; gap; gap >>= 1) {
    for (int i = gap; i < size; ++i) {
      Comparable tmp = std::move(a[i]);
      int j = i;
      for (; j >= gap && lessThan(tmp, a[j - gap]); j -= gap)
        a[j] = std::move(a[j - gap]);
      a[j] = std::move(tmp);
    }
  }
}

static inline int leftChild(int i) {
  return (i << 1) + 1;
}

template<typename Comparable, class Comparator=less<Comparable>>
void heapSort(vector<Comparable> &a, Comparator lessThan = Comparator()) {
}

template<typename Comparable, class Comparator=less<Comparable>>
void mergeSort(vector<Comparable> &a, Comparator lessThan = Comparator()) {
}

template<typename Comparable, class Comparator=less<Comparable>>
void quickSort(vector<Comparable> &a, Comparator lessThan = Comparator()) {
}

#endif //LEETCODE_SORT_H
