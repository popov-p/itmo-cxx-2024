#include <unordered_map>
#include <iostream>
#include <utility>
#include <map>

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

    ConstIterator cend() {
        return sortedData_.end();
    }

    size_t size() const { return data_.size(); }

    void clear() {
        data_.clear();
        sortedData_.clear();
    }
};

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
    std::unordered_map<Position, T, Matrix::pair_hash> data_;
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
        auto sortedData = matrix.sortedData_;
        for (const auto& [key, value] : sortedData) {
            os << "Row: " << key.first << ", Col: " << key.second << ", Value: " << value << std::endl;
        }
        return os;
    }

};

int main() {
    Vector<int> vec;
    vec.set(1, 10);
    vec.set(4, 24);
    vec.set(3, 20);

    std::cout << "Vector elements in sorted order:" << std::endl;
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        std::cout << "Index: " << it->first << ", Value: " << it->second << std::endl;
    }

    Matrix<int> mat;
    mat.set(0, 1, 5);
    mat.set(1, 0, 6);
    mat.set(2, 3, 15);
    mat.set(2, 4, 1);
    mat.set(1, 2, 10);

    std::cout << "\nMatrix elements in sorted order using iterator:" << std::endl;
    for (auto it = mat.begin(); it != mat.end(); ++it) {
        const auto& [key, value] = *it;
        std::cout << "Row: " << key.first << ", Col: " << key.second << ", Value: " << value << std::endl;
    }

    std::cout << "\nMatrix view:" << std::endl;
    std::cout << mat;

    return 0;
}
