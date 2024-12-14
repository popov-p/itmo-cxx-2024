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


TEST(MatrixTest, MatrixInverse) {
    Matrix<int> mat;
    mat.set(0, 0, 1);
    mat.set(0, 1, 2);
    mat.set(1, 0, 3);
    mat.set(1, 1, 4);

    EXPECT_THROW(mat.inverse(), std::runtime_error);
}

