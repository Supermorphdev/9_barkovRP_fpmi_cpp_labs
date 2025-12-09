#include "vector_impl.h"
#include <algorithm>
#include <cstring>

Vector::Vector() : data_(nullptr), size_(0), capacity_(0) {} //констр по умолч

Vector::Vector(size_t size) : size_(size), capacity_(size) { //констр с заданным размером
    if (size > 0) {
        data_ = new int[capacity_];
        std::fill(data_, data_ + size_, 0);
    }
    else {
        data_ = nullptr;
    }
}

Vector::Vector(std::initializer_list<int> list) : size_(list.size()), capacity_(list.size()) {
    if (size_ > 0) {
        data_ = new int[capacity_];
        std::copy(list.begin(), list.end(), data_);
    } 
    else {
        data_ = nullptr;
    }
}

Vector::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
    if (capacity_ > 0) {
        data_ = new int[capacity_];
        std::copy(other.data_, other.data_ + other.size_, data_);
    }
    else {
        data_ = nullptr;
    }
}

Vector::~Vector() {
    delete[] data_;
}

//Операторы
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        Vector temp(other);
        Swap(temp);
    }
    return *this;
}

void Vector::checkIndex(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index is out of range");
    }
}

int& Vector::operator[](size_t index) {
    return data_[index];
}

const int& Vector::operator[](size_t index) const {
    return data_[index];
}

int& Vector::At(size_t index) {
    checkIndex(index);
    return data_[index];
}

const int& Vector::At(size_t index) const {
    checkIndex(index);
    return data_[index];
}

size_t Vector::Size() const noexcept {
    return size_;
}

size_t Vector::Capacity() const noexcept {
    return capacity_;
}

bool Vector::Empty() const noexcept {
    return size_ == 0;
}

void Vector::PushBack(int value) {
    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        Reserve(new_capacity);
    }

    data_[size_] = value;
    ++size_;
}

void Vector::PopBack() {
    if (size_ > 0) {
        --size_;
    }
}

void Vector::Clear() noexcept {
    size_ = 0;
}

void Vector::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        int* new_data = new int[new_capacity];

        if (data_ != nullptr) {
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
        }

        data_ = new_data;
        capacity_ = new_capacity;
    }
}

void Vector::Swap(Vector& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << '[';
    for (size_t i = 0; i < vec.size_; ++i) {
        os << vec.data_[i];
        if (i < vec.size_ - 1) {
            os << ", ";
        }
    }
    os << ']';
    return os;
}


