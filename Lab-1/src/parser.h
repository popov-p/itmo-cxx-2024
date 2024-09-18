#ifndef PARSER_H
#define PARSER_H
#include <iostream>

class Parser {
public:
  Parser() = delete;
  static int parse_variables_count() {

    std::string input;
    int count;

    while (true) {
      std::cout << "Введите количество переменных [2 или 3]: ";
      std::getline(std::cin, input);
      try {
        count = std::stoi(input);

        if (count == 2 || count == 3) {
          std::cout << "Выбрано " << count << " переменных для сценария генерации." << std::endl;
          return count;
        } else {
          std::cerr << "Ошибка: Введено недопустимое количество переменных. Должно быть 2 или 3." << std::endl;
        }
      } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: Введено не число." << std::endl;
      } catch (const std::out_of_range& e) {
        std::cerr << "Ошибка: Число выходит за допустимый диапазон." << std::endl;
      }
    }
  }
};
#endif
