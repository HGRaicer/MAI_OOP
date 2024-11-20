#pragma once

#include "Shapes.h"


class ShapeArray {

    void resize(const size_t newCapacity) {
        auto const newShapes = new Shape*[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newShapes[i] = shapes[i];
        }
        delete[] shapes;
        shapes = newShapes;
        capacity = newCapacity;
    }

public:
    // Конструктор по умолчанию
    ShapeArray() : shapes(nullptr), size(0), capacity(0) {}

    // Конструктор с инициализацией из списка
    ShapeArray(std::initializer_list<Shape*> const initList)
        : shapes(new Shape*[initList.size()]), size(initList.size()), capacity(initList.size()) {
        size_t index = 0;
        for (Shape* shape : initList) {
            shapes[index++] = shape;
        }
    }

    // Деструктор
    ~ShapeArray() {
        delete[] shapes; // Освобождаем только массив, не управляем объектами внутри
    }

    // Добавление элемента
    void add(Shape* shape) {
        if (size == capacity) {
            resize(capacity == 0 ? 2 : capacity * 2);
        }
        shapes[size++] = shape;
    }

    // Удаление элемента
    void remove(const size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size - 1; ++i) {
            shapes[i] = shapes[i + 1];
        }
        --size;
    }

    // Доступ к элементу по индексу
    Shape* operator[](const size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return shapes[index];
    }

    // Получение текущего размера
    size_t getSize() const {
        return size;
    }

    // Очистка массива
    void clear() {
        size = 0;
    }
    Shape** begin() const {
        return shapes;
    }

    Shape** end() const {
        return shapes + size;
    }

private:
    Shape** shapes; // Указатель на массив указателей на Shape
    size_t size;    // Текущий размер списка
    size_t capacity; // Ёмкость массива
};