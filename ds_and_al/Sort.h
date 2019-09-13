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

static inline int _leftChild(int i) {
  return (i << 1) + 1;
}

template<typename Comparable, class Comparator=less<Comparable>>
static void _percolateDown(vector<Comparable> &a,
                           int i, int n,
                           Comparator lessThan) {
  int child;
  Comparable tmp = std::move(a[i]);

  for (; _leftChild(i) < n; i = child) {
    child = _leftChild(i);
    if (child != n - 1 && lessThan(a[child], a[child + 1]))
      ++child;
    if (lessThan(tmp, a[child]))
      a[i] = std::move(a[child]);
    else
      break;
  }
  a[i] = std::move(tmp);
}

template<typename Comparable, class Comparator=less<Comparable>>
void heapSort(vector<Comparable> &a, Comparator lessThan = Comparator()) {
  for (int i = a.size() / 2 - 1; i >= 0; --i)
    _percolateDown(a, i, a.size(), lessThan);
  for (int j = a.size() - 1; j > 0; --j) {
    std::swap(a[0], a[j]);
    _percolateDown(a, 0, j, lessThan);
  }
}

template<typename Comparable, class Comparator=less<Comparable>>
static void _merge(vector<Comparable> &a,
                   vector<Comparable> &tmpArray,
                   int leftPos, int rightPos, int rightEnd,
                   Comparator lessThan) {
  int leftEnd = rightPos - 1;
  int tmpPos = leftPos;
  int numElements = rightEnd - leftPos + 1;

  while (leftPos <= leftEnd && rightPos <= rightEnd) {
    if (lessThan(a[leftPos], a[rightPos]))
      tmpArray[tmpPos++] = std::move(a[leftPos++]);
    else
      tmpArray[tmpPos++] = std::move(a[rightPos++]);
  }

  while (leftPos <= leftEnd)
    tmpArray[tmpPos++] = std::move(a[leftPos++]);
  while (rightPos <= rightEnd)
    tmpArray[tmpPos++] = std::move(a[rightPos++]);

  for (int i = 0; i < numElements; ++i, --rightEnd)
    a[rightEnd] = std::move(tmpArray[rightEnd]);
}

template<typename Comparable, class Comparator=less<Comparable>>
static void _mergeSort(vector<Comparable> &a,
                       vector<Comparable> &tmpArray,
                       int left, int right,
                       Comparator lessThan = Comparator()) {
  if (left < right) {
    int center = (left + right) >> 1;
    _mergeSort(a, tmpArray, left, center, lessThan);
    _mergeSort(a, tmpArray, center + 1, right, lessThan);
    _merge(a, tmpArray, left, center + 1, right, lessThan);
  }
}

template<typename Comparable, class Comparator=less<Comparable>>
void mergeSort(vector<Comparable> &a, Comparator lessThan = Comparator()) {
  vector<Comparable> tmpArray(a.size());
  _mergeSort(a, tmpArray, 0, a.size() - 1, lessThan);
}

template<typename Comparable, class Comparator=less<Comparable>>
void quickSort(vector<Comparable> &a, Comparator lessThan = Comparator()) {
  if (a.size() <= 1)
    return;
  vector<Comparable> smaller, same, larger;

  auto chosenItem = a[a.size() >> 1];
  for (auto &i:a) {
    if (lessThan(i, chosenItem))
      smaller.push_back(i);
    else if (lessThan(chosenItem, i))
      larger.push_back(i);
    else
      same.push_back(i);
  }

  quickSort(smaller, lessThan);
  quickSort(larger, lessThan);

  std::move(begin(smaller), end(smaller), begin(a));
  std::move(begin(same), end(same), begin(a) + smaller.size());
  std::move(begin(larger), end(larger), end(a) - larger.size());
}

#endif //LEETCODE_SORT_H
