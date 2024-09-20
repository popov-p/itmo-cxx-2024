#include "parser.h"
#include "generator.h"

int main(int argc, char** argv) {
    std::vector<std::string> vartypes = Parser::parse_variable_types(Parser::parse_variables_count());
    auto gen = Generator();
    gen.parse_operations("../src/operations.txt");
    gen.print_operations();
    gen.generate(vartypes, "../src/f.cpp", 10);
    return 0;
}
