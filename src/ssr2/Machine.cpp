#include "ssr2/Machine.hpp"

ssr2::Machine::Machine() : _ps4Value() {}

void ssr2::Machine::update() noexcept {
    ssr2::PS4USB * ps4 = this->ps4();
    ps4->update();
    ps4->read(&_ps4Value);
    hand()->update();
    solenoid()->update();
    Adafruit_NeoPixel * pixels = this->pixels();
    if (pixels->canShow()) {
        pixels->show();
    }
}

void ssr2::Machine::reset() noexcept {
    lowerBody()->reset();
    forkLift()->reset();
    hand()->reset();
    arm()->reset();
    pixels()->clear();
}

bool ssr2::Machine::isPS4Connected() noexcept {
    ssr2::PS4USB * ps4 = this->ps4();
    if (ps4 == nullptr || ps4 == NULL) {
        return false;
    }
    return ps4->connected();
}

const ssr2::PS4Value & ssr2::Machine::currentPS4Value() const noexcept {
    return _ps4Value;
}
