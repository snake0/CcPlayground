//
// Created by SNAKE on 2019-09-09.
//

#ifndef LEETCODE_VECTOR_H
#define LEETCODE_VECTOR_H

#include <algorithm>

template<typename Object>
class Vector {
 public:
  explicit Vector(int initSize = 0)
    : theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY},
      objects{new Object[theCapacity]} {}

  Vector(int initSize, Object data) :
    theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY},
    objects{new Object[theCapacity]} {
    for (int k = 0; k < theSize; ++k)
      objects[k] = data;
  }

  Vector(const Vector &rhs)
    : theSize{rhs.theSize}, theCapacity{rhs.theCapacity} {
    objects = new Object[theCapacity];
    for (int k = 0; k < theSize; ++k)
      objects[k] = rhs.objects[k];
  }

  ~Vector() { delete[]objects; }

  Vector(Vector &&rhs)
    : theSize{rhs.theSize}, theCapacity{rhs.theCapacity},
      objects{rhs.objects} {
    rhs.objects = nullptr;
    rhs.theSize = 0;
    rhs.theCapacity = 0;
  }

  Vector &operator=(const Vector &rhs) {
    Vector copy(rhs);
    std::swap(*this, copy);
    return *this;
  }

  Vector &operator=(Vector &&rhs) {
    std::swap(theSize, rhs.theSize);
    std::swap(theCapacity, rhs.theCapacity);
    std::swap(objects, rhs.objects);

    return *this;
  }

  void resize(int newSize) {
    if (newSize > theCapacity)
      reserve(newSize << 1);
    theSize = newSize;
  }

  void reserve(int newCapacity) {
    if (newCapacity < theSize)
      return;

    Object *newArray = new Object[newCapacity];
    for (int k = 0; k < theSize; ++k)
      newArray[k] = std::move(objects[k]);

    theCapacity = newCapacity;
    std::swap(objects, newArray);
    delete[]newArray;
  }

  Object &operator[](int index) { return objects[index]; }

  const Object &operator[](int index) const { return objects[index]; }

  bool empty() const { return theSize == 0; }

  int size() const { return theSize; }

  int capacity() const { return theCapacity; }

  const Object *data() const { return objects; }

  void push_back(const Object &x) {
    if (theSize == theCapacity)
      reserve((theCapacity << 1) + 1);
    objects[theSize++] = x;
  }

  void push_back(Object &&x) {
    if (theSize == theCapacity)
      reserve((theCapacity << 1) + 1);
    objects[theSize++] = std::move(x);
  }

  void pop_back() { --theSize; }

  const Object &back() const { return objects[theSize - 1]; }

  typedef Object *iterator;
  typedef const Object *const_iterator;

  iterator begin() { return objects; }

  const_iterator begin() const { return objects; }

  iterator end() { return objects + theSize; }

  const_iterator end() const { return objects + theSize; }

  void swap(Vector &rhs) { std::swap(*this, rhs); }

  iterator erase(iterator pos) {

  }

  iterator erase(const_iterator pos) {

  }

  iterator erase(iterator first, iterator last) {

  }

  iterator erase(const_iterator first, const_iterator last) {

  }

  static const int SPARE_CAPACITY = 16;
 private:
  int theSize;
  int theCapacity;
  Object *objects;
};

#endif //LEETCODE_VECTOR_H
