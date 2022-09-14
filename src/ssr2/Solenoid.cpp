#include "ssr2/Solenoid.hpp"

ssr2::Solenoid::Solenoid(uint8_t pin, uint16_t duration)
: _pin(pin), _fired(false), duration(duration) {}

void ssr2::Solenoid::begin() noexcept {
    _pin.begin();
    _pin = false;
}

void ssr2::Solenoid::update() noexcept {
    if (!_fired) return;
    if (millis() - _fired >= duration) {
        _pin = false;
        _fired = false;
    }
}

void ssr2::Solenoid::fire() noexcept {
    _pin.write(true);
    _fired = true;
}

bool ssr2::Solenoid::isFired() const noexcept {
    return _fired;
}
