#include "ssr2/AnalogOut.hpp"

ssr2::AnalogOut::AnalogOut(uint8_t pin) : _pin(pin) {}

void ssr2::AnalogOut::begin() {
    pinMode(_pin, OUTPUT);
}

void ssr2::AnalogOut::write(uint8_t value) {
    analogWrite(_pin, value);
}

ssr2::AnalogOut& ssr2::AnalogOut::operator=(uint8_t value) {
    write(value);
    return *this;
}
