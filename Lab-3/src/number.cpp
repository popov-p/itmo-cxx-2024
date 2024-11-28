#include "number.h"


Number::Number() : value(0), text(nullptr) {
}

Number::Number(int val, const char* input) : value(val) {
    text = new char[std::strlen(input) + 1];
    std::strcpy(text, input); //NOLINT
}

Number::Number(const Number& other) : value(other.value) {
    text = new char[std::strlen(other.text) + 1];
    std::strcpy(text, other.text); //NOLINT
}

Number::~Number() {
    delete[] text;
}

void Number::print() const {
    std::cout << "Value: " << value << ", Text: " << text << std::endl;
}


std::ostream& operator<<(std::ostream& os, const Number& number) {
    return os;
}

std::ostream& operator<<(std::ostream& os, Number&& number) {
    return os;
}

bool operator<(const Number& lhs, const Number& rhs) {
    return lhs.value < rhs.value;
}

bool operator>(const Number& lhs, const Number& rhs) {
    return lhs.value > rhs.value;
}

Number operator+(const Number& lhs, const Number& rhs) {
    int new_value = lhs.value + rhs.value;

    size_t length_lhs = std::strlen(lhs.text);
    size_t length_rhs = std::strlen(rhs.text);
    size_t new_text_length = (length_lhs + length_rhs) / 2;

    char* new_text = new char[new_text_length + 1];
    for (size_t i = 0; i < new_text_length; ++i) {
        new_text[i] = 'a' + std::rand() % 26;
    }
    new_text[new_text_length] = '\0';

    Number result(new_value, new_text);

    delete[] new_text;

    return result;
}

Number operator/(const Number& lhs, size_t divisor) {
    if (divisor == 0) {
        throw std::runtime_error("Division by zero");
    }

    int new_value = lhs.value / static_cast<int>(divisor);

    char* new_text = new char[std::strlen(lhs.text) + 1];
    std::strcpy(new_text, lhs.text); //NOLINT

    Number result(new_value, new_text);

    delete[] new_text;

    return result;
}

bool operator%(const Number& num, int divisor) {
    if (divisor == 0) {
        throw std::invalid_argument("Division by zero is not allowed in operator %");
    }
    return num.value % divisor != 0;
}
