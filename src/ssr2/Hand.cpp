#include "ssr2/Hand.hpp"

ssr2::Hand::Hand(int16_t minAngle, int16_t maxAngle)
: ConstrainedMServo(minAngle, maxAngle), _angle(0) {}

void ssr2::Hand::write(int16_t angle) {
    _angle = constrain(angle, minAngle, maxAngle);
}

int16_t ssr2::Hand::read() {
    return _angle;
}

void ssr2::Hand::begin(int16_t angle) {
    ConstrainedMServo::begin(angle);
    _angle = angle;
}

void ssr2::Hand::update() {
    ConstrainedMServo::write(_angle);
    _angle = ConstrainedMServo::read();
    #ifdef ssr2_verbose
    char buffer[256] = "";
    snprintf_P(buffer, 200, PSTR("[ssr2::Hand] set angle as %d\n"), _angle);
    Serial.print(buffer);
    #endif /* ssr2_verbose */
}
