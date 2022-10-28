#pragma once

#include "ssr2/type_traits.hpp"
#include <Arduino.h>

namespace ssr2 {

template <typename T>
class Vector2D {
public:
    using Value = decltype(T(0));

    T x;
    T y;

    explicit Vector2D(T x = 0, T y = 0) : x(x), y(y) {}

    Vector2D() = delete;
    Vector2D(const Vector2D &) = default;
    Vector2D &operator=(const Vector2D &) = default;
    Vector2D(Vector2D &&) = default;
    Vector2D &operator=(Vector2D &&) = default;
    ~Vector2D() = default;

    template <typename U>
    constexpr auto dot(const Vector2D<U> &v) const noexcept
        -> decltype(x * v.x + y * v.y) {
        return x * v.x + y * v.y;
    }

    template <typename U>
    constexpr auto dot(U vx, U vy) const noexcept -> decltype(x * vx + y * vy) {
        return x * vx + y * vy;
    }

    inline auto angle() const noexcept -> decltype(atan2(y, x)) {
        return atan2(y, x);
    }

    constexpr auto magSq() const noexcept -> decltype(x * x + y * y) {
        return x * x + y * y;
    }

    inline auto mag() const noexcept -> decltype(sqrt(magSq())) {
        return sqrt(magSq());
    }
}; // class Vector2D

} // namespace ssr2

template <typename T1, typename T2>
bool operator==(const ssr2::Vector2D<T1> &lh, const ssr2::Vector2D<T2> &rh) {
    return lh.x == rh.x && lh.y == rh.y;
}

template <typename T1, typename T2>
bool operator!=(const ssr2::Vector2D<T1> &lh, const ssr2::Vector2D<T2> &rh) {
    return lh.x != rh.x || lh.y != rh.y;
}

template <typename T1, typename T2>
ssr2::Vector2D<T1> &operator+=(ssr2::Vector2D<T1> &lh,
                               const ssr2::Vector2D<T2> &rh) {
    lh.x += rh.x;
    lh.y += rh.y;
    return lh;
}

template <typename T1, typename T2>
ssr2::Vector2D<T1> &operator-=(ssr2::Vector2D<T1> &lh,
                               const ssr2::Vector2D<T2> &rh) {
    lh.x -= rh.x;
    lh.y -= rh.y;
    return lh;
}

template <typename T1, typename T2>
auto operator+(const ssr2::Vector2D<T1> &lh, const ssr2::Vector2D<T2> &rh)
    -> ssr2::Vector2D<decltype(lh.x + rh.x)> {
    return ssr2::Vector2D<decltype(lh.x + rh.x)>{lh.x + rh.x, lh.y + rh.y};
}

template <typename T1, typename T2>
auto operator-(const ssr2::Vector2D<T1> &lh, const ssr2::Vector2D<T2> &rh)
    -> ssr2::Vector2D<decltype(T1(0) - T2(0))> {
    return ssr2::Vector2D<decltype(T1(0) - T2(0))>{lh.x - rh.x, lh.y - rh.y};
}
