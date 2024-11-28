#pragma once

#include <iostream>
#include <cstring>

class Number {
public:
    Number();
    Number(int val, const char* input);
    Number(const Number& other);
    Number& operator=(const Number& other) {
        //std::cout << "Assignment operator (copy)" << std::endl;
        if (this == &other) {
            return *this;
        }

        value = other.value;

        delete[] text;
        text = new char[std::strlen(other.text) + 1];
        std::strcpy(text, other.text); //NOLINT

        return *this;
    }
    Number(Number&& other) noexcept : value(other.value), text(other.text) {
        //std::cout << "Move constructor" << std::endl;
        other.text = nullptr;
    }
    Number& operator=(Number&& other) noexcept {
        //std::cout << "Assignment operator (move)" << std::endl;
        if (this == &other) {
            return *this;
        }

        value = other.value;

        delete[] text;

        text = other.text;
        other.text = nullptr;

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Number& number);
    friend std::ostream& operator<<(std::ostream& os, Number&& number);
    friend bool operator<(const Number& lhs, const Number& rhs);
    friend bool operator>(const Number& lhs, const Number& rhs);
    friend Number operator+(const Number& lhs, const Number& rhs);
    friend Number operator/(const Number& lhs, size_t divisor);
    friend bool operator%(const Number& num, int divisor);


    ~Number();
    void print() const;
private:
    int value;
    char* text;

};


