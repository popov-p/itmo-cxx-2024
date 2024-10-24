#pragma once

#include <iostream>
#include <cstring>

class Number {
private:
    int value;
    char* text = nullptr;

public:

    Number() : value(0), text(nullptr) {
        std::cout << "Default constructor" << std::endl;
    }

    Number(int val, const char* input) : value(val) {
        std::cout << "Constructor" << std::endl;
        text = new char[std::strlen(input) + 1];
        std::strcpy(text, input); //NOLINT
    }

    Number(const Number& other) : value(other.value) {
        std::cout << "Copy constructor" << std::endl;
        text = new char[std::strlen(other.text) + 1];
        std::strcpy(text, other.text); //NOLINT
    }

    Number& operator=(const Number& other) {
        std::cout << "Assignment operator (copy)" << std::endl;
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
        std::cout << "Move constructor" << std::endl;
        other.text = nullptr;
    }

    Number& operator=(Number&& other) noexcept {
        std::cout << "Assignment operator (move)" << std::endl;
        if (this == &other) {
            return *this;
        }

        value = other.value;

        delete[] text;

        text = other.text;
        other.text = nullptr;

        return *this;
    }

    ~Number() {
        std::cout << "Destructor" << std::endl;
        delete[] text;
    }

    // Вывод на экран
    void print() const {
        std::cout << "Value: " << value << ", Text: " << text << std::endl;
    }
};
