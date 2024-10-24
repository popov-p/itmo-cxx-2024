#include "number.h"
#include <vector>

Number processVal(Number num) {
    num.print();
    return num;
}

Number& processRef(Number& num) {
    num.print();
    return num;
}


void processVector(std::vector<Number>& numbers) {
    for (Number& num : numbers) {
        num.print();
    }
}

std::vector<Number> createVector() {
    std::vector<Number> vec;
    vec.push_back(Number(1, "one"));
    std::cout << "---\n" << std::flush;
    vec.push_back(Number(2, "two"));
    std::cout << "---\n" << std::flush;
    vec.push_back(Number(3, "three"));
    std::cout << "---\n" << std::flush;
    vec.push_back(Number(4, "four"));
    std::cout << "---\n" << std::flush;
    vec.push_back(Number(5, "five"));
    std::cout << "---\n" << std::flush;
    return vec;
}
