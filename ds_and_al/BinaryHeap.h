//
// Created by SNAKE on 9/13/19.
//

#ifndef LEETCODE_BINARYHEAP_H
#define LEETCODE_BINARYHEAP_H

#include "include_for_cc.h"

#define LCHILD(x) ((x) << 1)
#define RCHILD(x) (((x) << 1) + 1)
#define PARENT(x) ((x) >> 1)

template<class Comparable, class Comparator=less<Comparable>>
class BinaryHeap {
 public:
//  BinaryHeap();
  explicit BinaryHeap(int capacity = 100);
  explicit BinaryHeap(const vector<Comparable> &items);
  explicit BinaryHeap(vector<Comparable> &&items);

  bool isEmpty() const;
  bool isHeap() const;
  const Comparable &top() const;

  void push(const Comparable &x);
  void push(Comparable &&x);
  void pop();
  void pop(Comparable &t);
  void makeEmpty();

  void print(ostream &out = cout);

 private:
  int currentSize;
  vector<Comparable> array;
  Comparator lessThan;

  void buildHeap();
  void percolateDown(int hole);
};

template<class Comparable, class Comparator>
BinaryHeap<Comparable, Comparator>::
BinaryHeap(int capacity)
  :currentSize{0}, array{vector<Comparable>(capacity)} {
  lessThan = Comparator();
}

template<class Comparable, class Comparator>
BinaryHeap<Comparable, Comparator>::
BinaryHeap(const vector<Comparable> &items)
  :array(items.size() + 10), currentSize{items.size()} {
  lessThan = Comparator();
  int size = items.size();

  for (int i = 0; i < size; ++i)
    array[i + 1] = items[i];
  buildHeap();
}

template<class Comparable, class Comparator>
BinaryHeap<Comparable, Comparator>::
BinaryHeap(vector<Comparable> &&items)
  :array(items.size() + 10), currentSize{static_cast<int>(items.size())} {
  lessThan = Comparator();
  int size = items.size();

  for (int i = 0; i < size; ++i)
    array[i + 1] = std::move(items[i]);
  buildHeap();
}

template<class Comparable, class Comparator>
bool BinaryHeap<Comparable, Comparator>::isEmpty() const {
  return currentSize == 0;
}

template<class Comparable, class Comparator>
const Comparable &BinaryHeap<Comparable, Comparator>::top() const {
  return;
}

template<class Comparable, class Comparator>
void BinaryHeap<Comparable, Comparator>::push(const Comparable &x) {
  ++currentSize;
  if (currentSize == array.size())
    array.resize(array.size() << 1);

  int hole = currentSize;
  Comparable copy = x;

  array[0] = std::move(copy);
  for (; lessThan(x, array[PARENT(hole)]); hole >>= 1)
    array[hole] = std::move(array[PARENT(hole)]);
  array[hole] = std::move(array[0]);
}

template<class Comparable, class Comparator>
void BinaryHeap<Comparable, Comparator>::push(Comparable &&x) {
  ++currentSize;
  if (currentSize == array.size())
    array.resize(array.size() << 1);

  int hole = currentSize;

  array[0] = std::move(x);
  for (; lessThan(x, array[PARENT(hole)]); hole >>= 1)
    array[hole] = std::move(array[PARENT(hole)]);
  array[hole] = std::move(array[0]);
}

template<class Comparable, class Comparator>
void BinaryHeap<Comparable, Comparator>::pop() {
  if (isEmpty())
    throw UnderflowException{};

  array[1] = std::move(array[currentSize--]);
  percolateDown(1);
}

template<class Comparable, class Comparator>
void BinaryHeap<Comparable, Comparator>::pop(Comparable &t) {
  if (isEmpty())
    throw UnderflowException{};

  t = std::move(array[1]);
  array[1] = std::move(array[currentSize--]);
  percolateDown(1);
}

template<class Comparable, class Comparator>
void BinaryHeap<Comparable, Comparator>::makeEmpty() {

}

template<class Comparable, class Comparator>
void BinaryHeap<Comparable, Comparator>::buildHeap() {
  for (int i = currentSize >> 1; i > 0; --i)
    percolateDown(i);
}

template<class Comparable, class Comparator>
void BinaryHeap<Comparable, Comparator>::percolateDown(int hole) {
  int child;
  Comparable t = std::move(array[hole]);

  for (; LCHILD(hole) <= currentSize; hole = child) {
    child = LCHILD(hole);

    if (child != currentSize && array[child + 1] < array[child])
      ++child;

    if (array[child] < t)
      array[hole] = std::move(array[child]);
    else break;
  }
  array[hole] = std::move(t);
}

template<class Comparable, class Comparator>
bool BinaryHeap<Comparable, Comparator>::isHeap() const {
  int p = 1;
  int lim = currentSize >> 1;

  for (; p <= lim; ++p) {
    if (!lessThan(array[p], array[LCHILD(p)]))
      return false;
    if (RCHILD(p) <= currentSize &&
        !lessThan(array[p], array[RCHILD(p)]))
      return false;
  }
  return true;
}

template<class Comparable, class Comparator>
void BinaryHeap<Comparable, Comparator>::print(ostream &out) {
  int level = 0;
  while ((1 << level) < currentSize)
    ++level;
  out<<level;
}


#endif //LEETCODE_BINARYHEAP_H
