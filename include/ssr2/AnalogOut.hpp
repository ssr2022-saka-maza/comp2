#pragma once

#include <Arduino.h>

namespace ssr2 {

class AnalogOut {
private:
    uint8_t _pin;

public:
    AnalogOut(uint8_t pin);
    ~AnalogOut() = default;
    void begin();
    void write(uint8_t value);
    AnalogOut &operator=(uint8_t value);
}; // class AnalogOut

} // namespace ssr2
