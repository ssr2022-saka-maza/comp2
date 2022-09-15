#include "ssr2/Motor.hpp"

ssr2::Motor::Motor(uint8_t dir, uint8_t pwm) : _dir(dir), _pwm(pwm) {}

void ssr2::Motor::begin() {
    _dir.begin();
    _pwm.begin();
}

void ssr2::Motor::write(int16_t value) {
    _dir = value >= 0;
    _pwm = abs(value);
    #ifdef ssr2_verbose
    char buffer[256] = "";
    snprintf_P(buffer, 255, PSTR("[ssr2::Motor] set power as %d\n"), value);
    Serial.print(buffer);
    #endif /* ssr2_verbose */
}

ssr2::Motor& ssr2::Motor::operator=(int16_t value) {
    write(value);
    return *this;
}
