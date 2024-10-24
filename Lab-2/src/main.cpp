#include "number.h"
#include "test.h"
#include <vector>
#include <list>
#include <iostream>
#include <vector>
#include <list>

int main() {
    std::cout << "Number staticNumber(100, \"one hundred\")" << std::endl;
    Number staticNumber(100, "one hundred");
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "Number* numberArray = new Number[size] ... (c-style)" << std::endl;
    int size = 4;
    Number* numberArray = new Number[size] {
        Number(1, "One"),
        Number(2, "Two"),
        Number(3, "Three"),
        Number()
    };


    delete[] numberArray;
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "Number* dynamicNumber = new Number(200, \"two hundred\")" << std::endl;
    Number* dynamicNumber = new Number(200, "two hundred");
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "std::vector<Number> numbers = createVector()" << std::endl;
    std::vector<Number> numbers = createVector();
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "processVector(numbers)" << std::endl;
    processVector(numbers);
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "numbers.push_back(staticNumber)" << std::endl;
    numbers.push_back(staticNumber);
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "numbers.push_back(*dynamicNumber)" << std::endl;
    numbers.push_back(*dynamicNumber);
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "std::list<Number> numberList = {Number(10, \"ten\"), Number(20, \"twenty\"), Number(30, \"thirty\")}" << std::endl;
    std::list<Number> numberList = {Number(10, "ten"), Number(20, "twenty"), Number(30, "thirty")};
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "for (auto& num : numberList) { num.print(); }" << std::endl;
    for (auto& num : numberList) {
        num.print();
    }
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "Number returnedByValue = processVal(staticNumber)" << std::endl;
    Number returnedByValue = processVal(staticNumber);
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "Number& returnedByReference = processRef(*dynamicNumber)" << std::endl;
    Number& returnedByReference = processRef(*dynamicNumber);
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "delete dynamicNumber" << std::endl;
    delete dynamicNumber;
    std::cout << "--------------------------------------------------------" << std::endl;

    return 0;
}
