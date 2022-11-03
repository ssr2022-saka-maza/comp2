#include "ssr2/AnalogOut.hpp"

ssr2::AnalogOut::AnalogOut(uint8_t pin) : _pin(pin) {}

void ssr2::AnalogOut::begin() {
    pinMode(_pin, OUTPUT);
}

void ssr2::AnalogOut::write(uint8_t value) {
#ifdef ssr2_verbose
    char buffer[256] = "";
    snprintf_P(buffer, 255, PSTR("[ssr2::AnalogOut] set pin %d as %d\n"), _pin, value);
    Serial.print(buffer);
#endif /* ssr2_verbose */
    analogWrite(_pin, value);
}

ssr2::AnalogOut & ssr2::AnalogOut::operator=(uint8_t value) {
    write(value);
    return *this;
}
