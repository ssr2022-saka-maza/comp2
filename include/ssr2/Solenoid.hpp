#pragma once

#include "ssr2/DigitalOut.hpp"
#include <Arduino.h>

namespace ssr2 {

class Solenoid {
private:
    DigitalOut _pin;
    bool _fired;
    uint64_t _lastFiredTime;

public:
    const uint16_t duration;

    explicit Solenoid(uint8_t pin, uint16_t duration = 1000);

    Solenoid() = delete;
    Solenoid(const Solenoid &) = delete;
    Solenoid &operator=(const Solenoid &) = delete;
    Solenoid(Solenoid &&) = delete;
    Solenoid &operator=(Solenoid &&) = delete;
    ~Solenoid() = default;

    void begin() noexcept;
    void update() noexcept;
    void fire() noexcept;
    bool isFired() const noexcept;
}; // class Solenoid

} // namespace ssr2
