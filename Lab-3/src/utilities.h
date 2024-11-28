#pragma once

#include "number.h"
#include <string>
#include <vector>
#include <list>


std::string generateRandomString(size_t length);
std::vector<Number> step1(const size_t& vector_size);
std::vector<Number> step2(const std::vector<Number>& v1);
std::pair<std::list<Number>, size_t> step3(std::vector<Number>& v1);
std::pair<std::list<Number>, size_t> step4(std::vector<Number>& v2);
void step5(std::pair<std::vector<Number>, size_t> p1,
           std::pair<std::vector<Number>, size_t> p2);
void step6(std::list<Number>& l1);
void step7(std::list<Number>& list2);
std::vector<Number> step8(std::vector<Number>& v1, std::vector<Number>& v2);
std::list<std::pair<Number, Number>> step9(const std::list<Number>& list1, const std::list<Number>& list2);
std::vector<std::pair<Number, Number>> step10(std::list<Number>& l1, std::list<Number>& l2);
