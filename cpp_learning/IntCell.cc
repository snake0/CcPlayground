//
// Created by SNAKE on 2019-09-08.
//

#include "IntCell.h"
#include "include_for_cc.h"

IntCell::IntCell(int initialValue) {
  cout << "Constructor basic\n";
  storedValue = new int(initialValue);
}

int IntCell::read() const {
  return *storedValue;
}

void IntCell::write(int x) {
  *storedValue = x;
}

IntCell::~IntCell() {
  cout << "Destructor\n";
  delete storedValue;
}

IntCell::IntCell(const IntCell& rhs) {
  storedValue = new int{*rhs.storedValue};
}

IntCell::IntCell(IntCell&& rhs) : storedValue{rhs.storedValue} {
  rhs.storedValue = nullptr;
}

IntCell& IntCell::operator=(const IntCell& rhs) {
//    if (this != &rhs)
//        *storedValue = *rhs.storedValue;
//    return *this;
  IntCell copy = rhs;
  std::swap(*this, copy);
  return *this;
}

IntCell& IntCell::operator=(IntCell&& rhs) {
  std::swap(storedValue, rhs.storedValue);
  return *this;
}
