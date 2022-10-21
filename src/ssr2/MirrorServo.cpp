#include "ssr2/MirrorServo.hpp"

ssr2::MirrorServo::MirrorServo()
    : _servo1(), _servo2() {}

ssr2::MirrorServo::MirrorServo(uint8_t pin1, uint8_t pin2)
    : _servo1(), _servo2() {
    attach(pin1, pin2);
}

uint16_t ssr2::MirrorServo::attach(uint8_t pin1, uint8_t pin2) {
    return (_servo2.attach(pin2) << 8) | _servo1.attach(pin1);
}

void ssr2::MirrorServo::write(int16_t value) {
    int16_t value2 = 180 - value;
    _servo1.write(value);
    _servo2.write(value2);
#ifdef ssr2_verbose
    char buffer[256] = "";
    snprintf_P(buffer, 200, PSTR("[ssr2::MirrorServo] write %d to servo1, %d to servo2"), value, value2);
    Serial.println(buffer);
#endif /* ssr2_verbose */
}

int16_t ssr2::MirrorServo::read() {
    int v1 = _servo1.read(), v2 = _servo2.read();
    bool valid = v1 + v2 == 180;
    if (!valid) {
        return -1;
    }
    return v1;
}
