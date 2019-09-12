//
// Created by SNAKE on 2019-09-10.
//

#ifndef LEETCODE_SORT_IMPL_H
#define LEETCODE_SORT_IMPL_H

#include "include_for_cc.h"

template<typename Comparable>
void insertionSort(vector<Comparable> &a) {
  int size = a.size();
  for (int p = 1; p < size; ++p) {
    Comparable tmp = std::move(a[p]);
    int j = p;
    for (; j && tmp < a[j - 1]; --j)
      a[j] = std::move(a[j - 1]);
    a[j] = std::move(tmp);
  }
}

template<typename Comparable>
void selectionSort(vector<Comparable> &a) {
  int size = a.size();
  for (int p = 0; p < size - 1; ++p) {
    int minIndex = p;
    for (int j = p + 1; j < size; ++j) {
      if (a[j] < a[minIndex]) {
        minIndex = j;
      }
    }
    std::swap(a[p], a[minIndex]);
  }
}

template<typename Comparable>
void bubbleSort(vector<Comparable> &a) {
  int size = a.size();
  for (int p = size - 2; p + 1; --p) {
    for (int j = p + 1; j < size; ++j) {
      if (a[j - 1] > a[j]) {
        std::swap(a[j], a[j - 1]);
      }
    }
  }
}

template<typename Comparable>
void shellSort(vector<Comparable> &a) {
  int size = a.size();
  for (int gap = size; gap; gap >>= 1) {
    for (int i = gap; i < size; ++i) {
      Comparable tmp = std::move(a[i]);
      int j=i;

    }
  }
}

template<typename Comparable>
void heapSort(vector<Comparable> &a) {
}

template<typename Comparable>
void mergeSort(vector<Comparable> &a) {
}

template<typename Comparable>
void Sort(vector<Comparable> &a) {
}

#endif //LEETCODE_SORT_IMPL_H
