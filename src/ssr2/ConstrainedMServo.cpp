#include "ssr2/ConstrainedMServo.hpp"

ssr2::ConstrainedMServo::ConstrainedMServo(int16_t minAngle, int16_t maxAngle)
: MirrorServo(), _initialAngle(0), minAngle(minAngle), maxAngle(maxAngle) {}

void ssr2::ConstrainedMServo::reset() noexcept {
    write(_initialAngle);
}

void ssr2::ConstrainedMServo::begin(int16_t angle) {
    MirrorServo::write(angle);
}

void ssr2::ConstrainedMServo::write(int16_t angle) {
    int16_t a = constrain(angle, minAngle, maxAngle);
    #ifdef ssr2_verbose
    char buffer[256] = "";
    snprintf_P(buffer, 255, PSTR("[ssr2::ConstrainedMServo] set angle as %d\n"), a);
    Serial.print(buffer);
    #endif /* ssr2_verbose */
    MirrorServo::write(a);
}
