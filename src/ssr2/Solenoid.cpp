#include "ssr2/Solenoid.hpp"

ssr2::Solenoid::Solenoid(uint8_t pin, uint16_t duration) :
    _pin(pin), _fired(false), _lastFiredTime(0), duration(duration) {}

void ssr2::Solenoid::begin() noexcept {
    _pin.begin();
    _pin = false;
}

void ssr2::Solenoid::update() noexcept {
    if (!_fired) {
        return;
    }
    if (millis() - _lastFiredTime >= duration) {
        _pin = false;
        _fired = false;
#ifdef ssr2_verbose
        Serial.println(F("[ssr2::Solenoid] chilled"));
#endif /* ssr2_verbose */
    }
}

void ssr2::Solenoid::fire() noexcept {
    _pin.write(true);
    _fired = true;
    _lastFiredTime = millis();
#ifdef ssr2_verbose
    Serial.println(F("[ssr2::Solenoid] fired"));
#endif /* ssr2_verbose */
}

bool ssr2::Solenoid::isFired() const noexcept { return _fired; }
