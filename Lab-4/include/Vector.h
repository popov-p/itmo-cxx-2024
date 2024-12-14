#pragma once
#include <unordered_map>
#include <map>
#include <cmath>

template <typename T>
class Vector {
    using Iterator = typename std::map<size_t, T>::iterator;
    using ConstIterator = typename std::map<size_t, T>::const_iterator;

    std::unordered_map<size_t, T> data_;
    std::map<size_t, T> sortedData_;

    void insertIntoSortedData(size_t pos, const T& value) {
        sortedData_[pos] = value;
    }

    void eraseFromSortedData(size_t pos) {
        sortedData_.erase(pos);
    }

public:
    Vector() = default;

    T operator[](size_t index) const {
        auto it = data_.find(index);
        return (it != data_.end()) ? it->second : T{};
    }

    void set(size_t index, const T& value) {
        if (data_.find(index) != data_.end())
            eraseFromSortedData(index);

        data_[index] = value;
        insertIntoSortedData(index, value);
    }

    void erase(size_t index) {
        data_.erase(index);
        eraseFromSortedData(index);
    }

    Iterator begin() {
        return sortedData_.begin();
    }

    Iterator end() {
        return sortedData_.end();
    }

    ConstIterator cbegin() const {
        return sortedData_.begin();
    }

    ConstIterator cend() const {
        return sortedData_.end();
    }

    size_t size() const { return data_.size(); }

    void clear() {
        data_.clear();
        sortedData_.clear();
    }

    Vector operator-() const {
        Vector result;
        for (const auto& [index, value] : sortedData_) {
            result.set(index, -value);
        }
        return result;
    }

    Vector operator+(const Vector& other) const {
        Vector result;
        for (const auto& [index, value] : sortedData_) {
            result.set(index, value + other[index]);
        }
        return result;
    }

    T dot(const Vector& other) const {
        T result = 0;
        for (const auto& [index, value] : sortedData_) {
            result += value * other[index];
        }
        return result;
    }
};
