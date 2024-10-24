#include "number.h"


Number::Number() : value(0), text(nullptr) {
    std::cout << "Default constructor" << std::endl;
}

Number::Number(int val, const char* input) : value(val) {
    std::cout << "Constructor" << std::endl;
    text = new char[std::strlen(input) + 1];
    std::strcpy(text, input); //NOLINT
}

Number::Number(const Number& other) : value(other.value) {
    std::cout << "Copy constructor" << std::endl;
    text = new char[std::strlen(other.text) + 1];
    std::strcpy(text, other.text); //NOLINT
}

Number::~Number() {
    std::cout << "Destructor" << std::endl;
    delete[] text;
}

void Number::print() const {
    std::cout << "Value: " << value << ", Text: " << text << std::endl;
}


std::ostream& operator<<(std::ostream& os, const Number& number) {
    os << "(<<) Value: " << number.value << ", Text: " << (number.text ? number.text : "null");
    return os;
}

std::ostream& operator<<(std::ostream& os, Number&& number) {
    os << "(<<) Moved Value: " << number.value << ", Text: " << (number.text ? number.text : "null");
    return os;
}
