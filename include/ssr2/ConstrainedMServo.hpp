#pragma once

#include <Arduino.h>
#include <Servo.h>

namespace ssr2 {

class ConstrainedMServo {
private:
    int16_t _initialAngle;
    Servo _servo1, _servo2;

public:
    const int16_t minAngle, maxAngle;

    explicit ConstrainedMServo(int16_t minAngle = 0, int16_t maxAngle = 180);

    uint16_t attach(uint8_t pin1, uint8_t pin2) noexcept;
    void begin(int16_t angle = 0) noexcept;
    void write(int16_t angle) noexcept;
    void reset() noexcept;
    int16_t read() noexcept;
};  // class ConstrainedMServo

}  // namespace ssr2
