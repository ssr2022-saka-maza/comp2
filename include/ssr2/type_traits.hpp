#pragma once

#include <Arduino.h>

namespace ssr2 {

struct true_type {
    static constexpr bool value = true;
};

struct false_type {
    static constexpr bool value = false;
};

template <bool cond, typename T>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
    using type = T;
};

template <typename T, typename U>
struct is_same : false_type {};

template <typename T>
struct is_same<T, T> : true_type {};

struct is_arithmetic_impl {
private:
    template <typename T>
    static auto check_add(T * t) -> decltype(*t + 0, true_type());
    template <typename T>
    static false_type check_add(...);

    template <typename T>
    static auto check_sub(T * t) -> decltype(*t - 0, true_type());
    template <typename T>
    static false_type check_sub(...);

    template <typename T>
    static auto check_mul(T * t) -> decltype(*t * 1, true_type());
    template <typename T>
    static false_type check_mul(...);

    template <typename T>
    static auto check_div(T * t) -> decltype(*t / 1, true_type());
    template <typename T>
    static false_type check_div(...);

public:
    template <typename T>
    static auto check(T * t) -> typename enable_if<
        decltype(check_add(t))::value && decltype(check_sub(t))::value && decltype(check_mul(
            t))::value && decltype(check_div(t))::value,
        true_type>::type;
    template <typename T>
    static false_type check(...);
};

template <typename T>
struct is_arithmetic : decltype(is_arithmetic_impl::check<T>(nullptr)) {};

}  // namespace ssr2
