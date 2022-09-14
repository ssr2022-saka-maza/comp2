#include "ssr2/LowerBody.hpp"

ssr2::LowerBody::LowerBody(
    uint8_t dir1, uint8_t pwm1,
    uint8_t dir2, uint8_t pwm2,
    uint8_t dir3, uint8_t pwm3,
    uint16_t movAveCapacity
) : _dir1(cos(PI / 2), sin(PI / 2)), _dir2(cos(PI * 7 / 6), sin(PI * 7 / 6)), _dir3(cos(PI * 11 / 6), sin(PI * 11 / 6)),
    _motor1(dir1, pwm1), _motor2(dir2, pwm2), _motor3(dir3, pwm3),
    _moving_average1(movAveCapacity), _moving_average2(movAveCapacity), _moving_average3(movAveCapacity)
{}

void ssr2::LowerBody::begin(float v_x, float v_y, float v_theta) {
    _motor1.begin();
    _motor2.begin();
    _motor3.begin();
    twist(v_x, v_y, v_theta);
}

void ssr2::LowerBody::_setPowers_raw(float v1, float v2, float v3) {
    _moving_average1.write(v1);
    _moving_average2.write(v2);
    _moving_average3.write(v3);
    int16_t p1 = static_cast<int16_t>(_moving_average1.read());
    int16_t p2 = static_cast<int16_t>(_moving_average2.read());
    int16_t p3 = static_cast<int16_t>(_moving_average3.read());
    _motor1.write(p1);
    _motor2.write(p2);
    _motor3.write(p3);
    #ifdef SSR_VERBOSE
    char buffer[256] = "";
    snprintf_P(buffer, 255, PSTR("[ssr2::LowerBody] set motor powers as %4d, %4d, %4d\n"), p1, p2, p3);
    Serial.print(buffer);
    #endif /* SSR_VERBOSE */
}

void ssr2::LowerBody::_setPowers_normalized(float v1, float v2, float v3) {
    float max_v = max(max(abs(v1), abs(v2)), abs(v3));
    float scale = 255.0 / max_v;
    _setPowers_raw(v1 * scale, v2 * scale, v3 * scale);
}

void ssr2::LowerBody::setPowers(float v1, float v2, float v3) {
    float max_v = max(max(abs(v1), abs(v2)), abs(v3));
    if (max_v > 255.0) {
        _setPowers_normalized(v1, v2, v3);
    } else {
        _setPowers_raw(v1, v2, v3);
    }
}

void ssr2::LowerBody::reset() {
    setPowers(0, 0, 0);
}

void ssr2::LowerBody::twist(float v_x, float v_y, float v_theta) {
    float v1 = _dir1.dot(v_x, v_y) + v_theta;
    float v2 = _dir2.dot(v_x, v_y) + v_theta;
    float v3 = _dir3.dot(v_x, v_y) + v_theta;
    setPowers(v1, v2, v3);
}

void ssr2::LowerBody::parallel(float v_x, float v_y) {
    twist(v_x, v_y, 0.0);
}

void ssr2::LowerBody::rotate(float v_theta) {
    twist(0.0, 0.0, v_theta);
}
