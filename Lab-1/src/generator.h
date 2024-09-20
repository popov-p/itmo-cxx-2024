#ifndef GENERATOR_H
#define GENERATOR_H

#include <unordered_set>
#include <vector>
#include <random>

using UIDis = std::uniform_int_distribution<>;
using URDis = std::uniform_int_distribution<>;

class Generator {
public:
    Generator() = default;
    void parse_operations(const std::string& operations_list_path);

    void print_operations() const;
    void generate(const std::vector<std::string>& vartypes, const std::string& outfile, int exprnum);
private:
    std::unordered_set<char> _operations;
    bool is_valid_operation(const std::string& line);
};
#endif // GENERATOR_H
