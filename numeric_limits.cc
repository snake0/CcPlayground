//
// Created by SNAKE on 2019-08-27.
//
#include "include.h"

int main() {
    std::cout << "type\tlowest()\tmin()\t\tmax()\n\n";

    std::cout << "uchar\t"
              << +std::numeric_limits<unsigned char>::lowest() << '\t' << '\t'
              << +std::numeric_limits<unsigned char>::min() << '\t' << '\t'
              << +std::numeric_limits<unsigned char>::max() << '\n';
    std::cout << "int\t"
              << std::numeric_limits<int>::lowest() << '\t'
              << std::numeric_limits<int>::min() << '\t'
              << std::numeric_limits<int>::max() << '\n';
    std::cout << "long\t"
              << std::numeric_limits<long>::lowest() << '\t'
              << std::numeric_limits<long>::min() << '\t'
              << std::numeric_limits<long>::max() << '\n';
    std::cout << "long long\t"
              << std::numeric_limits<long long>::lowest() << '\t'
              << std::numeric_limits<long long>::min() << '\t'
              << std::numeric_limits<long long>::max() << '\n';
}