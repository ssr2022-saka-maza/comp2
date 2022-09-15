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
    Serial.println(F("[ssr2::Hand] update"));
    #endif /* ssr2_verbose */
}
