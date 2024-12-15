#include <gtest/gtest.h>
#include "Vector.h"

TEST(VectorTest, EmptyVector) {
  Vector<double> vec;
  EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, SetAndAccess) {
  Vector<double> vec;
  vec.set(1, 5.0);
  vec.set(3, 10.0);

  EXPECT_EQ(vec[1], 5.0);
  EXPECT_EQ(vec[3], 10.0);
  EXPECT_EQ(vec[2], 0.0);

  EXPECT_EQ(vec.size(), 2);
}

TEST(VectorTest, Erase) {
  Vector<double> vec;
  vec.set(1, 5.0);
  vec.set(3, 10.0);
  vec.erase(1);

  EXPECT_EQ(vec[1], 0.0);
  EXPECT_EQ(vec[3], 10.0);
  EXPECT_EQ(vec.size(), 1);
}

TEST(VectorTest, Iterators) {
  Vector<double> vec;
  vec.set(2, 20.0);
  vec.set(1, 10.0);
  vec.set(3, 30.0);

  std::vector<size_t> indices;
  std::vector<double> values;

  for (auto it = vec.begin(); it != vec.end(); ++it) {
    indices.push_back(it->first);
    values.push_back(it->second);
  }

  EXPECT_EQ(indices, (std::vector<size_t>{1, 2, 3}));
  EXPECT_EQ(values, (std::vector<double>{10.0, 20.0, 30.0}));
}

TEST(VectorTest, Clear) {
  Vector<double> vec;
  vec.set(1, 5.0);
  vec.set(3, 10.0);
  vec.clear();

  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec[1], 0.0);
  EXPECT_EQ(vec[3], 0.0);
}

TEST(VectorTest, UnaryMinus) {
  Vector<double> vec;
  vec.set(1, 5.0);
  vec.set(3, -10.0);

  Vector<double> negVec = -vec;

  EXPECT_EQ(negVec[1], -5.0);
  EXPECT_EQ(negVec[3], 10.0);
}

TEST(VectorTest, AdditionOperator) {
  Vector<double> vec1;
  vec1.set(1, 5.0);
  vec1.set(2, 10.0);

  Vector<double> vec2;
  vec2.set(1, 15.0);
  vec2.set(3, 20.0);

  Vector<double> sumVec = vec1 + vec2;

  EXPECT_EQ(sumVec[1], 20.0);
  EXPECT_EQ(sumVec[2], 10.0);
  EXPECT_EQ(sumVec[3], 20.0);
}

TEST(VectorTest, DotProduct) {
  Vector<double> vec1;
  vec1.set(1, 3.0);
  vec1.set(2, 4.0);

  Vector<double> vec2;
  vec2.set(1, 2.0);
  vec2.set(2, 5.0);
  vec2.set(3, 7.0);

  double dotProduct = vec1.dot(vec2);

  EXPECT_EQ(dotProduct, 26.0); // 3*2 + 4*5
}


TEST(VectorScalarOperations, AddScalar) {
  Vector<double> vec;
  vec.set(0, 1.0);
  vec.set(1, 2.0);

  Vector<double> result = vec + 1.0;

  EXPECT_EQ(result[0], 2.0);
  EXPECT_EQ(result[1], 3.0);
}

TEST(VectorScalarOperations, SubtractScalar) {
  Vector<double> vec;
  vec.set(0, 5.0);
  vec.set(1, 10.0);

  Vector<double> result = vec - 2.0;

  EXPECT_EQ(result[0], 3.0);
  EXPECT_EQ(result[1], 8.0);
}

TEST(VectorScalarOperations, MultiplyScalar) {
  Vector<double> vec;
  vec.set(0, 2.0);
  vec.set(1, 4.0);

  Vector<double> result = vec * 3.0;

  EXPECT_EQ(result[0], 6.0);
  EXPECT_EQ(result[1], 12.0);
}

TEST(VectorScalarOperations, DivideScalar) {
  Vector<double> vec;
  vec.set(0, 9.0);
  vec.set(1, 15.0);

  Vector<double> result = vec / 3.0;

  EXPECT_EQ(result[0], 3.0);
  EXPECT_EQ(result[1], 5.0);
}

TEST(VectorScalarOperations, PowScalar) {
  Vector<double> vec;
  vec.set(0, 2.0);
  vec.set(1, 3.0);

  Vector<double> result = vec.pow(2.0);

  EXPECT_EQ(result[0], 4.0);
  EXPECT_EQ(result[1], 9.0);
}


