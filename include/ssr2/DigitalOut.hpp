#pragma once

#include <Arduino.h>

namespace ssr2 {
    class DigitalOut {
    private:
        uint8_t _pin;
    public:
        DigitalOut(uint8_t pin);
        ~DigitalOut() = default;
        void begin();
        void write(bool value);
        DigitalOut& operator=(bool value);
    }; // class DigitalOut
} // namespace ssr2