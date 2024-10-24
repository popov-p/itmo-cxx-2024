#include "number.h"
#include "test.h"
#include <vector>
#include <list>
#include <iostream>
#include <vector>
#include <list>

int main() {
    // stack variable
    std::cout << "Number stackNumber(100, \"one hundred\")" << std::endl;
    Number stackNumber(100, "one hundred");
    std::cout << "--------------------------------------------------------" << std::endl;


    //static variable
    std::cout << "Number staticNumber(100, \"one hundred\")" << std::endl;
    static Number staticNumber(100, "one hundred");
    std::cout << "--------------------------------------------------------" << std::endl;

    //dynamic variable
    std::cout << "Number* dynamicNumber = new Number(200, \"two hundred\")" << std::endl;
    Number* dynamicNumber = new Number(200, "two hundred");
    std::cout << "--------------------------------------------------------" << std::endl;




    // c-style processing
    std::cout << "Number* numberArray = new Number[size] ... (c-style)" << std::endl;
    int size = 4;
    Number* numberArray = new Number[size] {
        Number(1, "One"),
        Number(2, "Two"),
        Number(3, "Three"),
        Number()
    };
    std::cout << "--------------------------------------------------------" << std::endl;


    //processing by index
    std::cout << "std::cout << numberArray[0] << std::endl;"<< std::endl;
    std::cout << numberArray[0] << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;


    //dynamic array deletion
    std::cout << "delete[] numberArray;" << std::endl;
    delete[] numberArray;
    std::cout << "--------------------------------------------------------" << std::endl;


    //c-style processing again but inside functions
    std::cout << "createVector(size), processVector(...), deleteVector(...) (c-style)" << std::endl;
    Number* vec = createVector(size);
    vec[0] = Number(10, "Ten");
    vec[1] = Number(20, "Twenty");
    vec[2] = Number(30, "Thirty");
    vec[3] = Number(30, "Fourty");
    std::cout << "---" << std::endl;
    processVector(vec, size);
    std::cout << "---" << std::endl;
    deleteVector(vec);
    std::cout << "--------------------------------------------------------" << std::endl;


    //c++ style vector
    std::cout << "std::vector<Number> numbers = createVector()" << std::endl;
    std::vector<Number> numbers = createVector();
    std::cout << "--------------------------------------------------------" << std::endl;




    //vector processing inside function
    std::cout << "processVector(numbers)" << std::endl;
    processVector(numbers);
    std::cout << "--------------------------------------------------------" << std::endl;





    //push_back stack variable
    std::cout << "numbers.push_back(stackNumber)" << std::endl;
    numbers.push_back(stackNumber);
    std::cout << "--------------------------------------------------------" << std::endl;




    //push_back heap variable
    std::cout << "numbers.push_back(*dynamicNumber)" << std::endl;
    numbers.push_back(*dynamicNumber);
    std::cout << "--------------------------------------------------------" << std::endl;




    //usage in list
    std::cout << "std::list<Number> numberList = {Number(10, \"ten\"), Number(20, \"twenty\"), Number(30, \"thirty\")}" << std::endl;
    std::list<Number> numberList = {Number(10, "ten"), Number(20, "twenty"), Number(30, "thirty")};
    std::cout << "--------------------------------------------------------" << std::endl;




    //processing in list
    std::cout << "for (auto& num : numberList) { num.print(); }" << std::endl;
    for (auto& num : numberList) {
        num.print();
    }
    std::cout << "--------------------------------------------------------" << std::endl;




    //return value
    std::cout << "Number returnedByValue = processVal(stackNumber)" << std::endl;
    Number returnedByValue = processVal(stackNumber);
    std::cout << "--------------------------------------------------------" << std::endl;




    //return ref
    std::cout << "Number& returnedByReference = processRef(*dynamicNumber)" << std::endl;
    Number& returnedByReference = processRef(*dynamicNumber);
    std::cout << "--------------------------------------------------------" << std::endl;



    //dynamic number deletion
    std::cout << "delete dynamicNumber" << std::endl;
    delete dynamicNumber;
    std::cout << "--------------------------------------------------------" << std::endl;


    return 0;
}
