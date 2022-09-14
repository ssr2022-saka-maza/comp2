#include "ssr2/ConstrainedMServo.hpp"

ssr2::ConstrainedMServo::ConstrainedMServo(uint8_t minAngle, uint8_t maxAngle)
: MirrorServo(), minAngle(minAngle), maxAngle(maxAngle) {}

void ssr2::ConstrainedMServo::begin(uint8_t angle) {
    MirrorServo::write(angle);
}

void ssr2::ConstrainedMServo::write(uint8_t angle) {
    uint8_t a = constrain(angle, minAngle, maxAngle);
    MirrorServo::write(a);
}
