#include "utilities.h"
#include <algorithm>
#include <numeric>

std::string generateRandomString(size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "0123456789";
    const size_t max_index = sizeof(charset) - 1;
    std::string random_string;
    random_string.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        random_string += charset[std::rand() % max_index];
    }

    return random_string;
}

std::vector<Number> step1(const size_t& vector_size) {
    std::vector<Number> v1;
    for (size_t i = 0; i < vector_size; ++i) {
        v1.emplace_back(std::rand() % 1001, generateRandomString(5).c_str());
    }
    return v1;
}

std::vector<Number> step2(const std::vector<Number>& v1) {
    size_t b = std::rand() % v1.size();
    size_t e = b + 1 + (std::rand() % (v1.size() - b));
    std::vector<Number> v2(v1.begin() + b,
                           v1.begin() + e);
    return v2;
}

std::pair<std::list<Number>, size_t> step3(std::vector<Number>& v1) {
    auto n = 20 + (std::rand() % (50 - 20 + 1));
    n = std::min(n, static_cast<int>(v1.size()));
    std::partial_sort(v1.begin(), v1.begin() + n, v1.end(), std::greater<Number>());

    std::list<Number> list1;
    std::copy(v1.begin(), v1.begin() + n , std::back_inserter(list1));

    return {list1, n};
}

std::pair<std::list<Number>, size_t> step4(std::vector<Number>& v2) {
    auto n = 20 + (std::rand() % (50 - 20 + 1));
    n = std::min(n, static_cast<int>(v2.size()));
    std::partial_sort(v2.begin(), v2.begin() + n, v2.end());

    std::list<Number> list2;
    std::copy(v2.begin(), v2.begin() + n, std::back_inserter(list2));

    return {list2, n};
}

void step5(std::pair<std::vector<Number>, size_t> p1,
           std::pair<std::vector<Number>, size_t> p2) {
    p1.first.erase(p1.first.begin(), p1.first.begin() + p1.second);
    p2.first.erase(p2.first.begin(), p2.first.begin() + p2.second);
}

void step6(std::list<Number>& l1) {
    Number sum = std::accumulate(l1.begin(), l1.end(), Number{0, "zero"});
    Number average = sum / l1.size();
    std::vector<Number> vec(l1.begin(), l1.end());

    //auto partition_point = std::partition(vec.begin(), vec.end(), // NOLINT
    //                                      [average](const Number& num) {
    //                                          return num > average;
    //                                      });

    /* Заметим, что если в п. 3 сразу сделать "правильное" копирование при помощи std:back_inserter(list1),
     * то п.6 выполняется уже автоматически.
     * Для "демонстрации навыков работы с stl" я посчитал среднее значение и определил операторы >, /,
     * однако этого можно было вовсе не делать.
    */
}

void step7(std::list<Number>& l2) {
    l2.remove_if([](const Number& num) {
        return num % 2 != 0;
    });
}

std::vector<Number> step8(std::vector<Number>& v1, std::vector<Number>& v2) {
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::vector<Number> v3;

    /* std::set_union обязательно требует сортировки */
    std::set_union(v1.begin(), v1.end(),
                   v2.begin(), v2.end(),
                   std::back_inserter(v3));

    return v3;
}

std::list<std::pair<Number, Number>> step9(const std::list<Number>& l1, const std::list<Number>& l2) {
    auto l1_copy = l1;
    auto l2_copy = l2;

    size_t diff = std::abs(static_cast<int>(l1_copy.size()) - static_cast<int>(l2_copy.size()));

    if (l1_copy.size() > l2_copy.size()) {
        auto it = l1_copy.begin();
        std::advance(it, diff);
        l1_copy.erase(l1_copy.begin(), it);
    } else if (l2_copy.size() > l1_copy.size()) {
        auto it = l2_copy.begin();
        std::advance(it, diff);
        l2_copy.erase(l2_copy.begin(), it);
    }

    std::list<std::pair<Number, Number>> l3;

    std::transform(l1_copy.begin(), l1_copy.end(),
                   l2_copy.begin(), std::back_inserter(l3),
                   [](const Number& n1, const Number& n2) {
                       return std::make_pair(n1, n2);
                   });

    return l3;
}

std::vector<std::pair<Number, Number>> step10(std::list<Number>& l1, std::list<Number>& l2) {
    size_t n = std::min(l1.size(), l2.size());

    auto it1 = l1.begin();
    auto it2 = l2.begin();

    std::vector<std::pair<Number, Number>> list3;

    std::transform(it1, std::next(it1, n), it2, std::back_inserter(list3),
                   [](const Number& n1, const Number& n2) {
                       return std::make_pair(n1, n2);
                   });

    return list3;
}
