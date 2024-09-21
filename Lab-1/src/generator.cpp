#include "generator.h"

#include <format>
#include <sstream>
#include <iostream>
#include <fstream>

void Generator::parse_operations(const std::string& operations_list_path) {
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

void Generator::print_operations() const {
    std::cout << "Получены операции: ";
    for (const auto& op : _operations) {
        std::cout << op << " ";
    }
    std::cout << std::endl;
}

void Generator::generate(const std::vector<std::string>& vartypes, const std::string& outfile, int exprnum) {
    std::ofstream file(outfile);
    if (!file) {
        std::cout << "Не получилось создать файл: " + outfile << std::endl;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    UIDis udis(1, 100);
    URDis urealdis(1, 100);

    auto choose_random = [&](const auto& what) {
        UIDis dist(0, what.size() - 1);
        return what[dist(gen)];
    };

    std::vector<char> ops(_operations.begin(), _operations.end());

    file << "#include <iostream>\n\n";
    file << "int main() {\n";

    for(int i = 0; i < vartypes.size(); i++) {
        std::string vartype_i =  choose_random(vartypes);
        file << "  " << vartype_i << std::format(" var_{}", i) << " = ";
        if((vartype_i == "int") || (vartype_i == "long int")) {
            file << udis(rd) <<";\n";
        }
        else {            
            file << urealdis(rd) <<";\n";
        }
    }

    for (int i = 0; i < exprnum; i++) {
        std::stringstream expr;
        UIDis dist(0, vartypes.size() - 1);
        for (int j = 0; j < vartypes.size() - 1; j++) {
            expr << std::format(" var_{}", dist(gen));
            expr << " " << choose_random(ops);
        }
        expr << std::format(" var_{}", dist(gen));
        file << "  std::cout << \"Result of:\" << " << "\"" << expr.str() << "\"" << " << \" = \" << " << expr.str() << " << \"\\n\"" << ";\n";
    }
    file << "  return 0;\n}\n";
}

bool Generator::is_valid_operation(const std::string& line) {
    if (line.length() != 1) {
        return false;
    }
    char op = line[0];
    return op == '+' || op == '-' || op == '*' || op == '/';
}
