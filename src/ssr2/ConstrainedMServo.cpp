#include "ssr2/ConstrainedMServo.hpp"

ssr2::ConstrainedMServo::ConstrainedMServo(int16_t minAngle, int16_t maxAngle)
    : _initialAngle(0), minAngle(minAngle), maxAngle(maxAngle) {}

uint16_t ssr2::ConstrainedMServo::attach(uint8_t pin1, uint8_t pin2) {
    return (_servo2.attach(pin2) << 8) | _servo1.attach(pin1);
}

void ssr2::ConstrainedMServo::begin(int16_t angle) {
    _initialAngle = max(minAngle, min(maxAngle, angle));
    write(_initialAngle);
}

void ssr2::ConstrainedMServo::write(int16_t angle) {
    int16_t a = max(minAngle, min(angle, maxAngle));
    int16_t a2 = 180 - a;
    _servo1.write(a);
    _servo2.write(a2);
#ifdef ssr2_verbose
    char buffer[256] = "";
    snprintf_P(
        buffer, 200, PSTR("[ssr2::ConstrainedMServo] write %d to servo1, %d to servo2\n"), a, a2);
    Serial.print(buffer);
#endif /* ssr2_verbose */
}

void ssr2::ConstrainedMServo::reset() noexcept {
    write(_initialAngle);
}

int16_t ssr2::ConstrainedMServo::read() {
    int v1 = _servo1.read(), v2 = _servo2.read();
    bool valid = v1 + v2 == 180;
    if (!valid) {
        return -1;
    }
    return v1;
}
