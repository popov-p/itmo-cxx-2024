#pragma once
#include "Vector.h"
#include <cstddef>
#include <stdexcept>
#include <ostream>
#include <iostream>

template <typename T>
class Matrix {
  using Position = std::pair<size_t, size_t>;
  using Iterator = typename std::map<Position, T>::iterator;
  using ConstIterator = typename std::map<Position, T>::const_iterator;

  using pair_hash = struct pair_hash {
    template <typename U, typename V>
    size_t operator()(const std::pair<U, V>& pair) const {
      size_t h1 = std::hash<U>{}(pair.first);
      size_t h2 = std::hash<V>{}(pair.second);
      return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
  };


  std::unordered_map<Position, T, pair_hash> data_;
  std::map<Position, T> sortedData_;
  size_t maxRow_ = 0, maxCol_ = 0;
  void insertIntoSortedData(const Position& pos, const T& value) {
    sortedData_[pos] = value;
  }

  void eraseFromSortedData(const Position& pos) {
    sortedData_.erase(pos);
  }
public:
  Matrix() = default;

  bool find(const T& value) const {
    for (const auto& [position, element] : data_) {
      if (element == value)
        return true;
    }
    return false;
  }

    T operator()(size_t row, size_t col) const {
      auto it = data_.find({row, col});
      return (it != data_.end()) ? it->second : T{};
    }

    void set(size_t row, size_t col, const T& value) {
      const Position index = {row, col};

      if (data_.find(index) != data_.end()) {
        eraseFromSortedData(index);
      }

      data_[index] = value;
      insertIntoSortedData(index, value);
      maxRow_ = std::max(maxRow_, row);
      maxCol_ = std::max(maxCol_, col);
    }

    void erase(size_t row, size_t col) {
      const Position index = {row, col};
      data_.erase(index);
      eraseFromSortedData(index);

      maxRow_ = 0;
      maxCol_ = 0;

      for (const auto& [position, value] : data_) {
        maxRow_ = std::max(maxRow_, position.first);
        maxCol_ = std::max(maxCol_, position.second);
      }
    }

    size_t size() const { return data_.size(); }

    void clear() {
      data_.clear();
      sortedData_.clear();
    }

    Iterator begin() {
      return sortedData_.begin();
    }

    Iterator end() {
      return sortedData_.end();
    }

    ConstIterator cbegin() {
      return sortedData_.begin();
    }

    ConstIterator cend() {
      return sortedData_.end();
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
      for (size_t i = 0; i <= matrix.maxRow_; ++i) {
        for (size_t j = 0; j <= matrix.maxCol_; ++j) {
          os << matrix(i, j) << " ";
        }
        os << std::endl;
      }

      return os;
    }

    static Matrix identity(size_t size) {
      Matrix result;

      for (size_t i = 0; i <= size; ++i) {
        for (size_t j = 0; j <= size; ++j) {
          result.set(i, j, (i == j) ? 1 : 0);
        }
      }

      return result;
    }

    static Matrix zeros(size_t size) {
      Matrix result;

      for (size_t i = 0; i <= size; ++i) {
        for (size_t j = 0; j <= size; ++j) {
          result.set(i, j, 0);
        }
      }

      return result;
    }


    Matrix transpose() const {
      Matrix result;
      for (const auto& [position, value] : data_) {
        result.set(position.second, position.first, value);
      }
      return result;
    }

    Matrix operator+(const T& scalar) const {
      Matrix result;
      for (const auto& [position, value] : data_) {
        result.set(position.first, position.second, value + scalar);
      }
      return result;
    }

    Matrix operator-(const T& scalar) const {
      Matrix result;
      for (const auto& [position, value] : data_) {
        result.set(position.first, position.second, value - scalar);
      }
      return result;
    }


    Matrix operator+(const Matrix& other) const {
      Matrix result;
      for (const auto& [position, value] : data_) {
        result.set(position.first, position.second, value + other(position.first, position.second));
      }
      return result;
    }

    Matrix operator-(const Matrix& other) const {
      if (this->maxRow_ != other.maxRow_ || this->maxCol_ != other.maxCol_) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
      }

      Matrix result;
      for (const auto& [position, value] : data_) {
        result.set(position.first, position.second, value - other(position.first, position.second));
      }

      for (const auto& [position, value] : other.data_) {
        if (result.data_.find(position) == result.data_.end()) {
          result.set(position.first, position.second, -value);
        }
      }

      return result;
    }

    Vector<T> operator*(const Vector<T>& vec) const {
      Vector<T> result;
      for (const auto& [position, value] : data_) {
        size_t row = position.first;
        size_t col = position.second;
        result.set(row, result[row] + value * vec[col]);
      }
      return result;
    }

    Matrix operator*(const Matrix& other) const {
      size_t maxColA = 0;
      size_t maxRowB = 0;

      for (const auto& [positionA, valueA] : data_) {
        maxColA = std::max(maxColA, positionA.second);
      }

      for (const auto& [positionB, valueB] : other.data_) {
        maxRowB = std::max(maxRowB, positionB.first);
      }

      if (maxColA != maxRowB) {
        throw std::runtime_error("Matrix dimensions are incompatible for multiplication.");
      }

      Matrix result;

      for (const auto& [positionA, valueA] : data_) {
        size_t rowA = positionA.first;
        size_t colA = positionA.second;

        for (const auto& [positionB, valueB] : other.data_) {
          size_t rowB = positionB.first;
          size_t colB = positionB.second;

          if (colA == rowB) {
            result.set(rowA, colB, result(rowA, colB) + valueA * valueB);
          }
        }
      }

      return result;
    }

    Matrix operator*(const T& scalar) const {
      Matrix result;
      for (const auto& [position, value] : data_) {
        result.set(position.first, position.second, value * scalar);
      }
      return result;
    }

    Matrix operator/(const T& scalar) const {
      if (scalar == T(0)) {
        throw std::invalid_argument("Cannot divide by zero.");
      }

      Matrix result;
      for (const auto& [position, value] : data_) {
        result.set(position.first, position.second, value / scalar);
      }
      return result;
    }

    Matrix operator^(const T& exponent) const {
      Matrix result;
      for (const auto& [position, value] : data_) {
        result.set(position.first, position.second, std::pow(value, exponent));
      }
      return result;
    }


    bool operator==(const Matrix<T>& other) const {
      if (this->maxRow_ != other.maxRow_ || this->maxCol_ != other.maxCol_) {
        return false;
      }

      for (const auto& [position, value] : this->data_) {
        if (other.data_.find(position) == other.data_.end() || other(position.first, position.second) != value) {
          return false;
        }
      }

      return true;
    }


    Matrix power(int exp) const {
      if(!isSquare())
        throw std::invalid_argument("Matrix must be square.");

      Matrix result = *this;

      if (exp == 0)
        return Matrix::identity(maxRow_);

      for (int i = 1; i < exp; ++i) {
        result = result * *this;
      }

      return result;
    }

    Matrix pow(double p, int approxOrder = 100) {
      if (!isSquare()) {
        throw std::invalid_argument("Matrix must be square to compute power.");
      }

      Matrix logA = log(approxOrder);

      Matrix pLogA = logA * p;

      return pLogA.exp(approxOrder);
    }


    Matrix log(int approxOrder = 100) {
      if (!isSquare()) {
        throw std::invalid_argument("Matrix must be square to compute the logarithm.");
      }

      Matrix I = Matrix::identity(maxRow_);
      if (*this == I) {
        return Matrix::zeros(maxRow_);
      }

      if (frobeniusNorm(*this) >= 1)
        throw std::invalid_argument("Frobenius matrix norm must be less than 1.");

      Matrix A_minus_I = *this - I;
      Matrix result = Matrix::zeros(maxRow_);
      Matrix term = A_minus_I;

      for (int n = 1; n <= approxOrder; ++n) {
        if (n > 1) {
          term = term * A_minus_I;
        }
        if (n % 2 == 0) {
          result = result - term / static_cast<T>(n);
        } else {
          result = result + term / static_cast<T>(n);
        }
      }

      return result;
    }

    double frobeniusNorm(const Matrix& matrix) {
      double norm = 0.0;
      for (size_t i = 0; i <= matrix.maxRow_; ++i) {
        for (size_t j = 0; j <= matrix.maxCol_; ++j) {
          norm += std::pow(std::abs(matrix(i, j)), 2);
        }
      }
      return std::sqrt(norm);
    }

    Matrix exp(int approxOrder = 100) const {
      if(!isSquare())
        throw std::invalid_argument("Matrix must be square to compute the exponential.");

      // exp(A) = I + A + A^2/2! + A^3/3! + ...

      Matrix<T> result = Matrix::identity(maxRow_);

      Matrix<T> term = *this;
      result = result + term;


      for (size_t n = 2; n < approxOrder; ++n) {
        term = term * *this;
        term = term / static_cast<T>(n);

        result = result + term;
      }

      return result;
    }

    bool isSquare() const {
      return maxRow_ == maxCol_;
    }

    Matrix inverse() const {
      if (!isSquare()) {
        throw std::invalid_argument("Matrix must be square.");
      }

      int rows = maxRow_ + 1;
      int cols = maxCol_ + 1;

      Matrix augmentedMatrix;
      augmentedMatrix.maxRow_ = rows;
      augmentedMatrix.maxCol_ = 2 * cols;

      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          augmentedMatrix.set(i, j, (*this)(i, j));
          augmentedMatrix.set(i, j + cols, (i == j) ? 1.0 : 0.0);
        }
      }
      std::cout << augmentedMatrix;

      for (int i = 0; i < rows; ++i) {
        int maxRow = i;
        for (int j = i + 1; j < rows; ++j) {
          if (std::abs(augmentedMatrix(i, j)) > std::abs(augmentedMatrix(maxRow, i))) {
            maxRow = j;
          }
        }

        if (maxRow != i) {
          for (int j = 0; j < 2 * cols; ++j) {
            double temp = augmentedMatrix(i, j);
            augmentedMatrix.set(i, j, augmentedMatrix(maxRow, j));
            augmentedMatrix.set(maxRow, j, temp);
          }
        }

        double pivot = augmentedMatrix(i, i);
        if (pivot == 0) {
          throw std::runtime_error("Matrix is singular and cannot be inverted.");
        }

        for (int j = 0; j < 2 * cols; ++j) {
          double value = augmentedMatrix(i, j) / pivot;
          augmentedMatrix.set(i, j, value);
        }

        for (int j = 0; j < rows; ++j) {
          if (i != j) {
            double factor = augmentedMatrix(j, i);
            for (int k = 0; k < 2 * cols; ++k) {
              double value = augmentedMatrix(j, k) - factor * augmentedMatrix(i, k);
              augmentedMatrix.set(j, k, value);
            }
          }
        }
      }

      Matrix inverseMatrix;
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          double value = augmentedMatrix(i, j + cols);
          inverseMatrix.set(i, j, value);
        }
      }

      return inverseMatrix;
    }

  };
