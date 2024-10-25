#include "Six.h"
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <iostream>

Six::Six() {
    _size = 0;
    _data = new unsigned char[1]{0};  // Устанавливаем 0
}

Six::Six(const size_t &size, unsigned int data) {
    _size = size;
    _data = new unsigned char[size]{};

    for (size_t i = 0; i < size && data; ++i) {
        _data[i] = data % 6;
        data /= 6;
    }
}

Six::Six(const std::initializer_list<unsigned char> &list) {
    if (list.size() == 0) {
        throw std::invalid_argument("List is empty");
    }
    _size = list.size();
    _data = new unsigned char[_size]{};
    size_t i = 0;
    for (auto it : list) {
        if (it > 5) {
            throw std::invalid_argument("List contains invalid data");
        }
        _data[i++] = it;
    }
}

Six::Six(const std::string &str) {
    if (str.empty()) {
        throw std::invalid_argument("String is empty");
    }
    _size = str.size();
    _data = new unsigned char[_size]{};
    for (size_t i = 0; i < _size; ++i) {
        if (str[i] > '5' || str[i] < '0') {
            throw std::invalid_argument("String contains invalid data");
        }
        _data[i] = str[i] - '0';
    }
}

std::ostream &Six::print(std::ostream &os) {
    for (size_t i = 0; i < _size; ++i) {
        os << static_cast<int>(_data[_size - i - 1]);
    }
    return os;
}

Six::Six(const Six &other) {
    _size = other._size;
    _data = new unsigned char[_size]{};
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
}

Six::Six(Six &&other) noexcept {
    _size = other._size;
    _data = other._data;
    other._size = 0;
    other._data = nullptr;
}

Six Six::sum(const Six &other) const {
    size_t max_size = _size > other._size ? _size : other._size;
    Six result(max_size, 0);
    int sum = 0;
    size_t i = 0;

    for (; i < std::min(_size, other._size); ++i) {
        sum += _data[i] + other._data[i];
        result._data[i] = sum % 6;
        sum /= 6;
    }

    for (; i < _size; ++i) {
        sum += _data[i];
        result._data[i] = sum % 6;
        sum /= 6;
    }

    for (; i < other._size; ++i) {
        sum += other._data[i];
        result._data[i] = sum % 6;
        sum /= 6;
    }

    if (sum) {
        auto *tmp = new unsigned char[max_size + 1]{};
        for (size_t j = 0; j < max_size; ++j) {
            tmp[j] = result._data[j];
        }
        delete[] result._data;
        result._data = tmp;
        result._data[max_size] = sum;
        result._size++;
    }

    return result;
}

Six Six::subtract(const Six &other) const {
    if (this->less(other)) {
        throw std::invalid_argument("Cannot subtract");
    }

    Six result(_size, 0);
    int diff = 0;
    size_t i = 0;

    for (; i < other._size; ++i) {
        diff += _data[i] - other._data[i] + 6;
        result._data[i] = diff % 6;
        diff = diff / 6 - 1;
    }

    for (; i < _size; ++i) {
        diff += _data[i] + 6;
        result._data[i] = diff % 6;
        diff = diff / 6 - 1;
    }

    if (diff != 0) {
        throw std::invalid_argument("Cannot subtract");
    }

    while (result._size > 1 && result._data[result._size - 1] == 0) {
        --result._size;
    }

    return result;
}

bool Six::more(const Six &other) const {
    return compare(other) > 0;
}

bool Six::less(const Six &other) const {
    return compare(other) < 0;
}

bool Six::equal(const Six &other) const {
    return compare(other) == 0;
}

int Six::compare(const Six &other) const {
    if (_size > other._size) return 1;
    if (_size < other._size) return -1;

    for (int i = _size - 1; i >= 0; --i) {
        if (_data[i] > other._data[i]) return 1;
        if (_data[i] < other._data[i]) return -1;
    }
    return 0;
}

Six::~Six() noexcept {
    delete[] _data;
    _data = nullptr;
    _size = 0;
}
