//
// Created by SNAKE on 2019-09-08.
//

#include <iostream>
#include "IntCell.h"
#include "include_for_cc.h"

using namespace std;

typedef vector<IntCell> IntCells;

int randItem(IntCells&& rcells) {
    cout << "rvalue\n";
    return rcells[rand() % rcells.size()].read();
}

int randItem(const IntCells& lcells) {
    cout << "lvalue\n";
    return lcells[rand() % lcells.size()].read();
}

int main() {
    cout << randItem({IntCell(1)});
}