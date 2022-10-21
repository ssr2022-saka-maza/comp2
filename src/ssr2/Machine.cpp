#include "ssr2/Machine.hpp"

ssr2::Machine::Machine() : _ps4Value() {}

void ssr2::Machine::update() noexcept {
    ssr2::PS4USB *ps4 = ps4_();
    ps4->update();
    ps4->read(&_ps4Value);
    hand_()->update();
    solenoid_()->update();
}

void ssr2::Machine::reset() noexcept {
    lowerBody_()->reset();
    forkLift_()->reset();
    hand_()->reset();
    arm_()->reset();
}

bool ssr2::Machine::isPS4Connected() noexcept {
    ssr2::PS4USB *ps4 = ps4_();
    if (ps4 == nullptr || ps4 == NULL) {
        return false;
    }
    return ps4->connected();
}

const ssr2::PS4Value &ssr2::Machine::currentPS4Value() const noexcept {
    return _ps4Value;
}
