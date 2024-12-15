 #include "Matrix.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

template <typename T>
class StdBasedMatrix {
public:
  StdBasedMatrix(size_t rows, size_t cols, double sparsity = 0.7)
      : rows_(rows), cols_(cols), sparsity_(sparsity) {
    data_.resize(rows, std::vector<T>(cols, 0));
    fillWithRandomValues();
  }

  T get(size_t row, size_t col) const {
    if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("Index out of range.");
    }
    return data_[row][col];
  }

  void set(size_t row, size_t col, T value) {
    if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("Index out of range.");
    }
    data_[row][col] = value;
  }

  bool find(T value) const {
    for (size_t i = 0; i < rows_; ++i) {
      for (size_t j = 0; j < cols_; ++j) {
        if (data_[i][j] == value) {
          return true;
        }
      }
    }
    return false;
  }

  void print() const {
    for (const auto& row : data_) {
      for (const auto& elem : row) {
        std::cout << elem << " ";
      }
      std::cout << std::endl;
    }
  }

private:
  size_t rows_, cols_;
  double sparsity_; // Вероятность появления ненулевого значения
  std::vector<std::vector<T>> data_;

  void fillWithRandomValues() {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (size_t i = 0; i < rows_; ++i) {
      for (size_t j = 0; j < cols_; ++j) {
        // С вероятностью (1 - sparsity_) заполняем нулём
        if ((rand() % 100) / 100.0 < sparsity_) {
          data_[i][j] = static_cast<T>(rand() % 100 + 1);
        }
      }
    }
  }
};

std::vector<double> generateSparsities() {
  std::vector<double> sparsities;

  for (int i = 1; i <= 20; ++i) {
    sparsities.push_back(i / 100.0);
  }

  for (int i = 3; i <= 10; ++i) {
    sparsities.push_back(i * 0.1);
  }

  return sparsities;
}

int main() {
  auto sparsities = generateSparsities();
  std::vector<int> dimensions = {500, 1000};
  for (const auto& dim : dimensions) {
    std::ofstream file (std::format(  "dim_{}.csv", dim), std::ios_base::trunc);
    if (!file.tellp()) {
      file << "Sparsity,CustomMatrixTime,StdBasedMatrixTime\n";
    }
    for (const auto& sparsity : sparsities) { // Вероятность появления ненулевого значения (sparsity% не нули)
      StdBasedMatrix<int> stdBasedMatrix(dim, dim, sparsity); // Заполняется случайными данными в конструкторе

      Matrix<int> customMatrix;
      for (size_t i = 0; i < dim; ++i) {
        for (size_t j = 0; j < dim; ++j) {
          int el = stdBasedMatrix.get(i, j);
          if (el)
            customMatrix.set(i, j, stdBasedMatrix.get(i, j));
        }
      }

      std::vector<int> nonZeroElements; // Элементы, которые будем искать
      for (auto it = customMatrix.cbegin(); it != customMatrix.cend(); ++it)
        nonZeroElements.push_back(it->second);


      auto start = std::chrono::high_resolution_clock::now();
      for (const auto& value : nonZeroElements) {
        customMatrix.find(value);
      }
      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> customMatrixSearchTime = end - start;
      std::cout << "Search time for non-zero elements in customMatrix: "
                << customMatrixSearchTime.count() << " seconds\n";

      start = std::chrono::high_resolution_clock::now();
      for (const auto& value : nonZeroElements) {
        stdBasedMatrix.find(value);
      }
      end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> stdBasedMatrixSearchTime = end - start;
      std::cout << "Search time for non-zero elements in stdBasedMatrix: "
                << stdBasedMatrixSearchTime.count() << " seconds\n\n";

      file << sparsity << ","
           << customMatrixSearchTime.count() << ","
           << stdBasedMatrixSearchTime.count() << "\n";
    }
  }
  return 0;
}
