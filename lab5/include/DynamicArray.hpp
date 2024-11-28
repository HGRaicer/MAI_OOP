#pragma once

#include <memory_resource>
#include <stdexcept>

#include "MyIterator.hpp"

template<typename T>
class DynamicArray {
private:
    T* data;
    size_t capacity;
    size_t size;
    std::pmr::polymorphic_allocator<T> allocator;

    /// Reallocates the internal array to the given capacity.  Moves all current
    /// elements to the new array, and deallocates the old array.  If the new
    /// capacity is less than the current size, the trailing elements are dropped.
    void resize(size_t new_capacity) {
        T* new_data = allocator.allocate(new_capacity);
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        allocator.deallocate(data, capacity);
        data = new_data;
        capacity = new_capacity;
    }

public:
    explicit DynamicArray(std::pmr::memory_resource* resource)
        : capacity(10), size(0), allocator(resource) {
        data = allocator.allocate(capacity);
    }


    ~DynamicArray() {
        allocator.deallocate(data, capacity);
      }

    /**
     * Adds a new element to the end of the dynamic array.
     * If the current size equals the capacity, the array is resized to accommodate more elements.
     *
     * @param value The element to be added to the array. It is moved into the array.
     */
    void push_back(T&& value) {
        if (size == capacity) {
          resize(capacity * 2);
        }
        allocator.construct(data + size++, std::forward<T>(value));
      }

    void push_back(const T& value) {
        if (size == capacity) {
          resize(capacity * 2);
        }
        allocator.construct(data + size++, value);
      }

    void clear() {
        size = 0;
    }

    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    bool empty() const {
        return size == 0;
    }

    size_t get_size() const {
        return size;
    }

    using Iterator = MyIterator<T>;
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size); }
};

