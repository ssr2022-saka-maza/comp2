#pragma once

#include <Arduino.h>
#include <Servo.h>

namespace ssr2 {

class MirrorServo {
private:
    Servo _servo1, _servo2;

public:
    explicit MirrorServo();
    explicit MirrorServo(uint8_t pin1, uint8_t pin2);

    MirrorServo(const MirrorServo &) = delete;
    MirrorServo & operator=(const MirrorServo &) = delete;
    MirrorServo(MirrorServo &&) = delete;
    MirrorServo & operator=(MirrorServo &&) = delete;
    ~MirrorServo() = default;

    uint16_t attach(uint8_t pin1, uint8_t pin2) noexcept;
    void write(int16_t value) noexcept;
    int16_t read() noexcept;
};  // class MirrorServo

}  // namespace ssr2
