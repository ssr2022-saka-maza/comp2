#include "ssr2/DigitalOut.hpp"

ssr2::DigitalOut::DigitalOut(uint8_t pin) : _pin(pin) {}

void ssr2::DigitalOut::begin() {
    pinMode(_pin, OUTPUT);
}

void ssr2::DigitalOut::write(bool value) {
    digitalWrite(_pin, value);
}

ssr2::DigitalOut& ssr2::DigitalOut::operator=(bool value) {
    write(value);
    return *this;
}
