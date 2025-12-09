#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <initializer_list>

class Vector {
private:
    int* data_;
    size_t size_;
    size_t capacity_;

    void checkIndex(size_t index) const;

public:
    //КОНСТУКТОРЫ
    Vector();
    explicit Vector(size_t size);
    Vector(std::initializer_list<int> list);
    Vector(const Vector& other);

    ~Vector(); //ДЕСТРУКТОР

    //ОПЕРАТОРЫ

    Vector& operator=(const Vector& other);

    //методы доступа

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    int& At(size_t index);
    const int& At(size_t index) const;

    //методы операций
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
    bool Empty() const noexcept;

    //методы модификации
    void PushBack(int value);
    void PopBack();
    void Clear() noexcept;
    void Reserve(size_t new_capacity);

    //метод обмена
    void Swap(Vector& other);
    
    //оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);
};
std::ostream& operator<<(std::ostream& os, const Vector& vec);

#endif  // VECTOR_H