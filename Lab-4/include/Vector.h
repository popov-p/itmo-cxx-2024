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
  std::size_t lastIndex_ = -1;
  void insertIntoSortedData(size_t pos, const T& value) {
    sortedData_[pos] = value;
    lastIndex_ = std::max(lastIndex_, pos);
  }

  void eraseFromSortedData(size_t pos) {
    sortedData_.erase(pos);
    if (!sortedData_.empty()) {
      lastIndex_ = sortedData_.rbegin()->first;
    } else {
      lastIndex_ = 0;
    }
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
    lastIndex_ = 0;
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

    const Vector* base = (this->lastIndex_ >= other.lastIndex_) ? this : &other;
    const Vector* secondary = (this->lastIndex_ < other.lastIndex_) ? this : &other;

    for (const auto& [index, value] : base->sortedData_)
      result.set(index, value);

    for (const auto& [index, value] : secondary->sortedData_)
      result.set(index, result[index] + value);

    result.lastIndex_ = base->lastIndex_;

    return result;
  }

  T dot(const Vector& other) const {
    T result = 0;
    for (const auto& [index, value] : sortedData_) {
      result += value * other[index];
    }
    return result;
  }

  Vector operator+(const T& scalar) const {
    Vector result;
    for (const auto& [index, value] : sortedData_) {
      result.set(index, value + scalar);
    }
    return result;
  }

  Vector operator-(const T& scalar) const {
    Vector result;
    for (const auto& [index, value] : sortedData_) {
      result.set(index, value - scalar);
    }
    return result;
  }

  Vector operator*(const T& scalar) const {
    Vector result;
    for (const auto& [index, value] : sortedData_) {
      result.set(index, value * scalar);
    }
    return result;
  }

  Vector operator/(const T& scalar) const {
    Vector result;
    for (const auto& [index, value] : sortedData_) {
      result.set(index, value / scalar);
    }
    return result;
  }

  Vector pow(const T& exponent) const {
    Vector result;
    for (const auto& [index, value] : sortedData_) {
      result.set(index, std::pow(value, exponent));
    }
    return result;
  }
};
