#include "ssr2/DigitalOut.hpp"

ssr2::DigitalOut::DigitalOut(uint8_t pin) : _pin(pin) {}

void ssr2::DigitalOut::begin() {
    pinMode(_pin, OUTPUT);
}

void ssr2::DigitalOut::write(bool value) {
    digitalWrite(_pin, value);
    #ifdef ssr2_verbose
    char buffer[256] = "";
    snprintf_P(buffer, 255, PSTR("[ssr2::DigitalOut] set pin %d as %d\n"), _pin, value);
    Serial.print(buffer);
    #endif /* ssr2_verbose */
}

ssr2::DigitalOut& ssr2::DigitalOut::operator=(bool value) {
    write(value);
    return *this;
}
