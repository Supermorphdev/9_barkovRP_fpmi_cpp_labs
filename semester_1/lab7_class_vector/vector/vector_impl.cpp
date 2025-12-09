#include "vector_impl.h"
#include <algorithm>
#include <cstring>

Vector::Vector() : data_(nullptr), size_(0), capacity_(0) {} //default constructor

Vector::Vector(size_t size) : size_(size), capacity_(size) { //constructor with specified size
    if (size > 0) {
        data_ = new int[capacity_];
        std::fill(data_, data_ + size_, 0);
    }
    else {
        data_ = nullptr;
    }
}

Vector::Vector(std::initializer_list<int> list) : size_(list.size()), capacity_(list.size()) { //constructor frow init list
    if (size_ > 0) {
        data_ = new int[capacity_];
        std::copy(list.begin(), list.end(), data_);
    } 
    else {
        data_ = nullptr;
    }
}

Vector::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) { // copy constructor
    if (capacity_ > 0) {
        data_ = new int[capacity_];
        std::copy(other.data_, other.data_ + other.size_, data_);
    }
    else {
        data_ = nullptr;
    }
}

Vector::~Vector() {  //destructor
    delete[] data_;
}

//Operators
Vector& Vector::operator=(const Vector& other) { //operator assigments by copy
    if (this != &other) {
        Vector temp(other);
        Swap(temp);
    }
    return *this;
}

void Vector::checkIndex(size_t index) const { //index check operator
    if (index >= size_) {
        throw std::out_of_range("Index is out of range");
    }
}

int& Vector::operator[](size_t index) { // indexing operator (not constant one)
    return data_[index];
}

const int& Vector::operator[](size_t index) const { //(constant one)
    return data_[index];
}

int& Vector::At(size_t index) { //method At
    checkIndex(index);
    return data_[index];
}

const int& Vector::At(size_t index) const { // at method (constant)
    checkIndex(index);
    return data_[index];
}

size_t Vector::Size() const noexcept { //Size method 
    return size_;
}

size_t Vector::Capacity() const noexcept { // Capacity method
    return capacity_;
}

bool Vector::Empty() const noexcept { // Empty check method
    return size_ == 0;
}

void Vector::PushBack(int value) { //PushBack method
    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        Reserve(new_capacity);
    }

    data_[size_] = value;
    ++size_;
}

void Vector::PopBack() { //popback method
    if (size_ > 0) {
        --size_;
    }
}

void Vector::Clear() noexcept { //clear method
    size_ = 0;
}

void Vector::Reserve(size_t new_capacity) { //memory reserve method
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

void Vector::Swap(Vector& other) { //swap method
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

std::ostream& operator<<(std::ostream& os, const Vector& vec) { //output function
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


