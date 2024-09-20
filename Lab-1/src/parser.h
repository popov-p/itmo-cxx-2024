#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <set>

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

    static std::vector<std::string> parse_variable_types(int count) {
        std::set<std::string> allowed_types = {"int", "float", "double", "long int"};
        std::vector<std::string> types;
        std::string input;

        for (int i = 1; i <= count; ++i) {
            while (true) {
                std::cout << "Введите тип переменной #" << i << " (доступные: int, float, double, long int): ";
                std::getline(std::cin, input);
                if (allowed_types.find(input) != allowed_types.end()) {
                    types.push_back(input);
                    break;
                } else {
                    std::cerr << "Ошибка: Недопустимый тип данных. Повторите ввод." << std::endl;
                }
            }
        }

        std::cout << "Выбранные типы переменных: ";
        for (const auto& type : types) {
            std::cout << type << " ";
        }
        std::cout << std::endl;

        return types;
    }
};
#endif
