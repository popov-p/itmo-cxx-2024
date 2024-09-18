#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>

class Generator {
public:
  Generator(const std::string& operations_list_path) {
    std::ifstream file(operations_list_path);
    if (!file) {
      throw std::runtime_error("Файл:" << operations_list_path << " не существует.");
    }
  }
private:
  bool is_valid_operation(const std::string& line) {
    if (line.length() != 1) {
      return false;
    }
    char op = line[0];
    return op == '+' || op == '-' || op == '*' || op == '/';
  }
};
#endif
