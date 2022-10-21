#pragma once

#include "ssr2/AnalogOut.hpp"
#include "ssr2/DigitalOut.hpp"
#include <Arduino.h>

namespace ssr2 {

class Motor {
private:
    DigitalOut _dir;
    AnalogOut _pwm;

public:
    Motor(uint8_t dir, uint8_t pwm);
    ~Motor() = default;
    void begin();
    void write(int16_t value);
    Motor &operator=(int16_t value);
}; // class Motor

} // namespace ssr2
