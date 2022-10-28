#pragma once

#include <Arduino.h>

namespace ssr2 {

template <typename T, uint32_t N>
class LimitedVector {
private:
    T *_data;
    uint32_t _size = 0;

public:
    static constexpr uint32_t capacity = N;

    explicit LimitedVector() : _data(new T[N]{}) {}

    LimitedVector(const LimitedVector &) = delete;
    LimitedVector &operator=(const LimitedVector &) = delete;
    LimitedVector(LimitedVector &&) = delete;
    LimitedVector &operator=(LimitedVector &&) = delete;

    ~LimitedVector() { delete[] _data; }

    void push_back(const T &value) noexcept {
        if (_size < N) {
            _data[_size++] = value;
        }
    }

    void push_back(T &&value) noexcept {
        if (_size < N) {
            _data[_size++] = value;
        }
    }

    void pop_back() noexcept {
        if (_size > 0) {
            --_size;
        }
    }

    void clear() noexcept { _size = 0; }

    T &operator[](uint32_t index) noexcept { return _data[index]; }
    const T &operator[](uint32_t index) const noexcept { return _data[index]; }

    uint32_t size() const noexcept { return _size; }

    bool empty() const noexcept { return _size == 0; }

    bool full() const noexcept { return _size == N; }

    T *begin() noexcept { return _data; }

    const T *begin() const noexcept { return _data; }

    T *end() noexcept { return _data + _size; }

    const T *end() const noexcept { return _data + _size; }
}; // class LimitedVector

} // namespace ssr2
