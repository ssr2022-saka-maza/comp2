#pragma once

#include "ssr2/type_traits.hpp"
#include <Arduino.h>

namespace ssr2 {

template <typename T>
class MovingAverage {
    static_assert(
        is_arithmetic<T>::value, "template parameter of ssr2::MovingAverage must be arithmetic");

private:
    uint16_t _index;
    bool _cycled;
    T * _values;
    T _values_sum;

public:
    const uint16_t capacity;

    MovingAverage() = delete;
    MovingAverage(const MovingAverage &) = delete;
    MovingAverage & operator=(const MovingAverage &) = delete;
    MovingAverage(MovingAverage &&) = default;
    MovingAverage & operator=(MovingAverage &&) = default;

    explicit MovingAverage(uint16_t capacity)
        : _index(0), _cycled(false), _values(nullptr), _values_sum(0), capacity(capacity) {
        _values = new T[capacity]{};
    }

    ~MovingAverage() {
        delete[] _values;
    }

    T read() noexcept {
        if (_index == 0) {
            return static_cast<T>(0);
        }
        if (!_cycled) {
            return _values_sum / static_cast<T>(_index);
        }
        return _values_sum / static_cast<T>(capacity);
    }

    void write(T value) noexcept {
        _values_sum += value - _values[_index];
        _values[_index] = value;
        _index++;
        if (_index == capacity) {
            _index = 0;
            _cycled = true;
        }
    }

    void reset() noexcept {
        _index = 0;
        _cycled = false;
        _values_sum = 0;
        for (uint16_t i = 0; i < capacity; i++) {
            _values[i] = 0;
        }
    }
};  // class MovingAverage

}  // namespace ssr2
