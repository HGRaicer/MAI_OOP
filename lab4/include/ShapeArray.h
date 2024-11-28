#pragma once
#include <memory>
#include "Shapes.h"
#include <initializer_list>

template <class T>
class ShapeArray {

    void resize(const size_t newCapacity) {
        auto const newShapes = std::make_shared_for_overwrite<T[]>[newCapacity];
        for (size_t i = 0; i < size_; ++i) {
            newShapes[i] = shapes[i];
        }
        shapes = std::move(newShapes);
        capacity_ = newCapacity;
    }

public:
    // Конструктор по умолчанию
    ShapeArray() : shapes(nullptr), size_(0), capacity_(0) {}

    // Конструктор с инициализацией из списка
    ShapeArray(const std::initializer_list<T>& list)
    {
        capacity_ = list.size();
        size_ = list.size();
        shapes = std::make_shared_for_overwrite<T[]>(capacity_);

        std::copy_n(list.begin(), size_, begin());
    }

    // Добавление элемента
    void add(const T& shape) {
        if (size_ == capacity_) {
            resize(capacity_ == 0 ? 2 : capacity_ * 2);
        }
        shapes[size_++] = shape;
    }

    // Удаление элемента
    void remove(const size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size_ - 1; ++i) {
            shapes[i] = shapes[i + 1];
        }
        --size_;
    }

    // Доступ к элементу по индексу
    const T& operator[](const size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return this->shapes[index];
    }
    T& operator[](const size_t index){
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return this->shapes[index];
    }

    // Получение текущего размера
    size_t getSize() const {
        return size_;
    }

    // Очистка массива
    void clear() {
        size_ = 0;
    }
    T* begin() const {
        return shapes.get();
    }

    T* end() const {
        return shapes.get() + size_;
    }

private:
    std::shared_ptr<T[]> shapes; // Указатель на массив указателей на Shape
    size_t size_;    // Текущий размер списка
    size_t capacity_; // Ёмкость массива
};