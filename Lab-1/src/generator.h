#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <random>
#include <format>


class Generator {
public:
  Generator() = default;
  void parse_operations(const std::string& operations_list_path) {
    std::ifstream file(operations_list_path);
    if (!file) {
        std::cout << "Файл: " + operations_list_path + " не существует.";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
      if (is_valid_operation(line)) {
        _operations.insert(line[0]);
      }
    }
  }
  void print_operations() const {
    std::cout << "Получены операции: ";
    for (const auto& op : _operations) {
      std::cout << op << " ";
    }
    std::cout << std::endl;
  }
  void generate(const std::vector<std::string>& vartypes, const std::string& outfile, int exprnum) {
    std::ofstream file(outfile);
    if (!file) {
      std::cout << "Не получилось создать файл: " + outfile << std::endl;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> udis(0, 100);
    auto choose_random = [&](const auto& what) {
        std::uniform_int_distribution<> dist(0, what.size() - 1);
        return what[dist(gen)];
    };
    std::vector<char> ops(_operations.begin(), _operations.end());

    file << "#include <iostream>\n";
    file << "int main() {\n";

    for(int i = 0; i < vartypes.size(); i++) {
      file << choose_random(vartypes) << std::format("var_{}", i) << " = " << udis(rd) <<";\n";
    }

    for (int i = 0; i < exprnum; i++) { /*fix this !!!*/
      file << "std::cout << " << std::format("var_{}", i);
      for (int j = 0; j < _operations.size(); j++) {
        file << " " << choose_random(ops);
      }
      file << ";\n";
    }

    file << "\n";
    file << "\n";
    file << "\n";

  }
private:
  std::unordered_set<char> _operations;
  bool is_valid_operation(const std::string& line) {
    if (line.length() != 1) {
      return false;
    }
    char op = line[0];
    return op == '+' || op == '-' || op == '*' || op == '/';
  }
};
#endif
