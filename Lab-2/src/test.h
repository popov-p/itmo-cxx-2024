#pragma once

#include "number.h"
#include <vector>

Number processVal(Number num);

Number& processRef(Number& num);


void processVector(std::vector<Number>& numbers);

std::vector<Number> createVector();

Number* createVector(int size);

void processVector(Number* vec, int size);

void deleteVector(Number* vec);
