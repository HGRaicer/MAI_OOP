#pragma once
#include <iterator>

template<typename T>
class MyIterator {
private:
    T* ptr;

public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::forward_iterator_tag;

    explicit MyIterator(T* p) : ptr(p) {}

    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }

    MyIterator& operator++() {
        ++ptr;
        return *this;
    }


    MyIterator operator++(int) {
        MyIterator temp = *this;
        ++ptr;
        return temp;
    }

    bool operator==(const MyIterator& other) const { return ptr == other.ptr; }
    bool operator!=(const MyIterator& other) const { return ptr != other.ptr; }
};
