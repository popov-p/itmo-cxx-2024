#include <gtest/gtest.h>
#include "Matrix.h"
#include "Vector.h"

TEST(MatrixTest, DefaultConstructor) {
  Matrix<int> mat;
  EXPECT_EQ(mat.size(), 0);
}

TEST(MatrixTest, SetGetElement) {
  Matrix<int> mat;
  mat.set(1, 2, 5);
  EXPECT_EQ(mat(1, 2), 5);
  EXPECT_EQ(mat(0, 0), 0);
}

TEST(MatrixTest, ClearMatrix) {
  Matrix<int> mat;
  mat.set(1, 1, 3);
  mat.set(2, 2, 4);
  mat.clear();
  EXPECT_EQ(mat.size(), 0);
  EXPECT_EQ(mat(1, 1), 0);
}

TEST(MatrixTest, EraseElement) {
  Matrix<int> mat;
  mat.set(1, 1, 5);
  mat.erase(1, 1);
  EXPECT_EQ(mat.size(), 0);
  EXPECT_EQ(mat(1, 1), 0);
}

TEST(MatrixTest, TransposeMatrix) {
  Matrix<int> mat;
  mat.set(0, 0, 1);
  mat.set(0, 1, 2);
  mat.set(1, 0, 3);
  mat.set(1, 1, 4);

  Matrix<int> transposed = mat.transpose();

  EXPECT_EQ(transposed(0, 0), 1);
  EXPECT_EQ(transposed(0, 1), 3);
  EXPECT_EQ(transposed(1, 0), 2);
  EXPECT_EQ(transposed(1, 1), 4);
}

TEST(MatrixTest, MatrixAddition) {
  Matrix<int> mat1;
  mat1.set(0, 0, 1);
  mat1.set(0, 1, 2);

  Matrix<int> mat2;
  mat2.set(0, 0, 3);
  mat2.set(0, 1, 4);

  Matrix<int> result = mat1 + mat2;

  EXPECT_EQ(result(0, 0), 4);
  EXPECT_EQ(result(0, 1), 6);
}

TEST(MatrixTest, MatrixVectorMultiplication) {
  Matrix<int> mat;
  mat.set(0, 0, 1);
  mat.set(0, 1, 2);
  mat.set(1, 0, 3);
  mat.set(1, 1, 4);

  Vector<int> vec;
  vec.set(0, 5);
  vec.set(1, 6);

  Vector<int> result = mat * vec;
  EXPECT_EQ(result[0], 17);  // 1*5 + 2*6 = 17
  EXPECT_EQ(result[1], 39);  // 3*5 + 4*6 = 39
}

TEST(MatrixTest, MatrixMultiplicationValid) {
  Matrix<int> A;
  A.set(0, 0, 1);
  A.set(0, 1, 2);
  A.set(1, 0, 3);
  A.set(1, 1, 4);

  Matrix<int> B;
  B.set(0, 0, 5);
  B.set(0, 1, 6);
  B.set(1, 0, 7);
  B.set(1, 1, 8);

          // Expected result of A * B
  Matrix<int> expected;
  expected.set(0, 0, 19);  // 1*5 + 2*7
  expected.set(0, 1, 22);  // 1*6 + 2*8
  expected.set(1, 0, 43);  // 3*5 + 4*7
  expected.set(1, 1, 50);  // 3*6 + 4*8

  Matrix<int> result = A * B;

  for (const auto& [position, value] : expected) {
    ASSERT_EQ(result(position.first, position.second), value);
  }
}

TEST(MatrixTest, MatrixMultiplicationInvalid) {
  Matrix<int> A;
  A.set(0, 0, 1);
  A.set(0, 1, 2);
  A.set(1, 0, 3);

  Matrix<int> B;
  B.set(0, 0, 4);
  B.set(0, 1, 5);
  B.set(1, 0, 6);
  B.set(1, 1, 7);
  B.set(2, 0, 8);
  B.set(2, 1, 9);

  EXPECT_THROW({
    try {
      Matrix<int> result = A * B;
    } catch (const std::runtime_error& e) {
      EXPECT_STREQ(e.what(), "Matrix dimensions are incompatible for multiplication.");
      throw;
    }
  }, std::runtime_error);
}

TEST(MatrixTest, MatrixPowerValid) {
  Matrix<int> A;
  A.set(0, 0, 1);
  A.set(0, 1, 2);
  A.set(1, 0, 3);
  A.set(1, 1, 4);

  Matrix<int> expected;
  expected.set(0, 0, 7);  // 1*1 + 2*3
  expected.set(0, 1, 10); // 1*2 + 2*4
  expected.set(1, 0, 15); // 3*1 + 4*3
  expected.set(1, 1, 22); // 3*2 + 4*4

  Matrix<int> result = A.power(2);


  for (const auto& [position, value] : expected) {
    ASSERT_EQ(result(position.first, position.second), value);
  }
}

TEST(MatrixTest, MatrixPowerInvalid) {
  Matrix<int> A;
  A.set(0, 0, 1);
  A.set(0, 1, 2);
  A.set(0, 2, 3);
  A.set(1, 0, 4);

  EXPECT_THROW({
    try {
      A.power(2);
    } catch (const std::invalid_argument& e) {
      EXPECT_STREQ(e.what(), "Matrix must be square.");
      throw;
    }
  }, std::invalid_argument);
}


TEST(MatrixTest, MatrixPowerZero) {
  Matrix<int> A;
  A.set(0, 0, 1);
  A.set(0, 1, 2);
  A.set(1, 0, 3);
  A.set(1, 1, 4);

  Matrix<int> expected;
  expected.set(0, 0, 1);
  expected.set(0, 1, 0);
  expected.set(1, 1, 1);
  expected.set(1, 0, 0);

  Matrix<int> result = A.power(0);

  for (const auto& [position, value] : expected) {
    ASSERT_EQ(result(position.first, position.second), value);
  }
}

TEST(MatrixTest, MatrixPowerOne) {
  Matrix<int> A;
  A.set(0, 0, 1);
  A.set(0, 1, 2);
  A.set(1, 0, 3);
  A.set(1, 1, 4);

  Matrix<int> expected;
  expected.set(0, 0, 1);
  expected.set(0, 1, 2);
  expected.set(1, 0, 3);
  expected.set(1, 1, 4);

  Matrix<int> result = A.power(1);

  for (const auto& [position, value] : expected) {
    ASSERT_EQ(result(position.first, position.second), value);
  }
}

TEST(MatrixExpTest, SquareMatrixExpOnes) {
  Matrix<double> mat;

  mat.set(0, 0, 1);
  mat.set(0, 1, 1);
  mat.set(1, 0, 0);
  mat.set(1, 1, 1);

  Matrix<double> result = mat.exp();

  EXPECT_NEAR(result(0, 0), 2.718, 0.001);
  EXPECT_NEAR(result(0, 1), 2.718, 0.001);
  EXPECT_NEAR(result(1, 0), 0, 0.1);
  EXPECT_NEAR(result(1, 1), 2.718, 0.001);
}

TEST(MatrixExpTest, SquareMatrixExp) {
  Matrix<double> mat;

  mat.set(0, 0, 1);
  mat.set(0, 1, 2);
  mat.set(1, 0, 3);
  mat.set(1, 1, 4);

  Matrix<double> result = mat.exp();

  EXPECT_NEAR(result(0, 0), 51.968956, 0.001);
  EXPECT_NEAR(result(0, 1), 74.736564, 0.001);
  EXPECT_NEAR(result(1, 0), 112.1048468, 0.001);
  EXPECT_NEAR(result(1, 1), 164.073803, 0.001);
}


TEST(MatrixExpTest, NonSquareMatrixExp) {
  Matrix<double> mat;

  mat.set(0, 0, 1);
  mat.set(0, 1, 2);
  mat.set(0, 2, 3);
  mat.set(1, 0, 4);
  mat.set(1, 1, 5);
  mat.set(1, 2, 6);

  EXPECT_THROW(mat.exp(), std::invalid_argument);
}

TEST(MatrixExpTest, ZeroMatrixExp) {
  Matrix<double> mat;

  mat.set(0, 0, 0);
  mat.set(0, 1, 0);
  mat.set(1, 0, 0);
  mat.set(1, 1, 0);

  Matrix<double> result = mat.exp();

  EXPECT_EQ(result(0, 0), 1);
  EXPECT_EQ(result(0, 1), 0);
  EXPECT_EQ(result(1, 0), 0);
  EXPECT_EQ(result(1, 1), 1);
}

TEST(MatrixExpTest, OneByOneMatrixExp) {
  Matrix<double> mat;
  mat.set(0, 0, 2);

  Matrix<double> result = mat.exp();

  EXPECT_NEAR(result(0, 0), exp(2), 0.1);
}

TEST(MatrixLogTest, LogOfIdentityMatrix) {
  Matrix<double> A;
  A.set(0, 0, 1);
  A.set(1, 1, 1);

  Matrix<double> logA = A.log();

  EXPECT_EQ(logA(0, 0), 0);
  EXPECT_EQ(logA(1, 1), 0);
}

TEST(MatrixLogTest, LogOfMatrixWithExpectedValues) {
  Matrix<double> A;
  A.set(0, 0, 0.5);
  A.set(0, 1, 0.2);
  A.set(1, 0, 0.1);
  A.set(1, 1, 0.4);

  Matrix<double> logA = A.log();

  EXPECT_NEAR(logA(0, 0), -0.741875, 1e-6);
  EXPECT_NEAR(logA(0, 1),  0.462098, 1e-6);
  EXPECT_NEAR(logA(1, 0),  0.231049, 1e-6);
  EXPECT_NEAR(logA(1, 1), -0.972924, 1e-6);
}

TEST(MatrixLogTest, LogOfNonSquareMatrixThrowsException) {
  Matrix<double> A;
  A.set(0, 0, 1);
  A.set(0, 1, 2);

  EXPECT_THROW(A.log(), std::invalid_argument);
}

TEST(MatrixPowTest, IdentityMatrix) {
  Matrix identity = Matrix<double>::identity(3);

  Matrix result1 = identity.pow(2.5);
  Matrix result2 = identity.pow(-1.0);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i == j) {
        EXPECT_DOUBLE_EQ(result1(i, j), 1.0);
        EXPECT_DOUBLE_EQ(result2(i, j), 1.0);
      } else {
        EXPECT_DOUBLE_EQ(result1(i, j), 0.0);
        EXPECT_DOUBLE_EQ(result2(i, j), 0.0);
      }
    }
  }
}

// TEST(MatrixPowTest, DiagonalMatrix) {
//   Matrix<double> diagonal;
//   diagonal.set(0, 0, 0.4);
//   diagonal.set(1, 1, 0.7);
//   diagonal.set(2, 2, 0.9);

//   Matrix<double> expected;
//   expected.set(0, 0std::pow(0.4, 0.5);
//   expected(1, 1) = std::pow(0.7, 0.5);
//   expected(2, 2) = std::pow(0.9, 0.5);

//   EXPECT_TRUE(diagonal.pow(0.5).isApprox(expected));
// }

TEST(MatrixPowTest, GeneralCase) {
  Matrix<double> A;
  A.set(0, 0, 0.2);
  A.set(0, 1, 0.1);
  A.set(1, 0, 0.4);
  A.set(1, 1, 0.5);

  Matrix<double> expected;
  expected.set(0, 0, 0.407902);
  expected.set(0, 1, 0.0916738);
  expected.set(1, 0, 0.366695);
  expected.set(1, 1, 0.682923);

  Matrix<double> result = A.pow(0.5);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_NEAR(result(i, j), expected(i, j), 1e-3);
    }
  }
}


// TEST(MatrixPowTest, InvalidCases) {
//   // Невырожденная матрица
//   Matrix singular(2, 2);
//   singular(0, 0) = 0; singular(0, 1) = 0;
//   singular(1, 0) = 0; singular(1, 1) = 0;

//           // Ожидаем исключение для невырожденной матрицы
//   EXPECT_THROW(singular.pow(0.5), std::invalid_argument);

//           // Ожидаем исключение для неквадратной матрицы
//   Matrix nonSquare(2, 3);
//   EXPECT_THROW(nonSquare.pow(2.0), std::invalid_argument);
// }


