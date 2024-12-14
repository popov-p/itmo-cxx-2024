#pragma once
#include "Vector.h"
#include <cstddef>
#include <stdexcept>
#include <ostream>

template <typename T>
class Matrix {
    using Position = std::pair<size_t, size_t>;
    using Iterator = typename std::map<Position, T>::iterator;
    using ConstIterator = typename std::map<Position, T>::const_iterator;

    using pair_hash = struct pair_hash {
        template <typename U, typename V>
        size_t operator()(const std::pair<U, V>& pair) const {
            return std::hash<U>()(pair.first) ^ (std::hash<V>()(pair.second) << 1);
        }
    };

    std::unordered_map<Position, T, pair_hash> data_;
    std::map<Position, T> sortedData_;

    void insertIntoSortedData(const Position& pos, const T& value) {
        sortedData_[pos] = value;
    }

    void eraseFromSortedData(const Position& pos) {
        sortedData_.erase(pos);
    }

public:
    Matrix() = default;

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
    }

    void erase(size_t row, size_t col) {
        const Position index = {row, col};
        data_.erase(index);
        eraseFromSortedData(index);
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
        size_t maxRow = 0;
        size_t maxCol = 0;
        for (const auto& [position, value] : matrix.sortedData_) {
            maxRow = std::max(maxRow, position.first);
            maxCol = std::max(maxCol, position.second);
        }

        for (size_t i = 0; i <= maxRow; ++i) {
            for (size_t j = 0; j <= maxCol; ++j) {
                os << matrix(i, j) << " ";
            }
            os << std::endl;
        }

        return os;
    }



    Matrix transpose() const {
        Matrix result;
        for (const auto& [position, value] : sortedData_) {
            result.set(position.second, position.first, value);
        }
        return result;
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (const auto& [position, value] : sortedData_) {
            result.set(position.first, position.second, value + other(position.first, position.second));
        }
        return result;
    }

    Vector<T> operator*(const Vector<T>& vec) const {
        Vector<T> result;
        for (const auto& [position, value] : sortedData_) {
            size_t row = position.first;
            size_t col = position.second;
            result.set(row, result[row] + value * vec[col]);
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        size_t maxColA = 0;
        size_t maxRowB = 0;

        for (const auto& [positionA, valueA] : sortedData_) {
            maxColA = std::max(maxColA, positionA.second);
        }

        for (const auto& [positionB, valueB] : other.sortedData_) {
            maxRowB = std::max(maxRowB, positionB.first);
        }

        if (maxColA != maxRowB) {
            throw std::runtime_error("Matrix dimensions are incompatible for multiplication.");
        }

        Matrix result;

        for (const auto& [positionA, valueA] : sortedData_) {
            size_t rowA = positionA.first;
            size_t colA = positionA.second;

            for (const auto& [positionB, valueB] : other.sortedData_) {
                size_t rowB = positionB.first;
                size_t colB = positionB.second;

                if (colA == rowB) {
                    result.set(rowA, colB, result(rowA, colB) + valueA * valueB);
                }
            }
        }

        return result;
    }



    Matrix power(int exp) const {
        if (sortedData_.size() != sortedData_.count({0, 0})) {
            throw std::invalid_argument("Matrix must be square.");
        }

        Matrix result = *this;
        for (int i = 1; i < exp; ++i) {
            result = result * *this;
        }
        return result;
    }

    Matrix inverse() const {
        if (sortedData_.size() != sortedData_.count({0, 0})) {
            throw std::invalid_argument("Matrix must be square.");
        }
        throw std::runtime_error("Inverse function is not implemented.");
    }
};