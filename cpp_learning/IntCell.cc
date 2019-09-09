//
// Created by SNAKE on 2019-09-08.
//

#include "IntCell.h"
#include "include_for_cc.h"

IntCell::IntCell(int initialValue) {
    storedValue = new int(initialValue);
}

int IntCell::read() const {
    return *storedValue;
}

void IntCell::write(int x) {
    *storedValue = x;
}

IntCell::~IntCell() {
    delete storedValue;
}