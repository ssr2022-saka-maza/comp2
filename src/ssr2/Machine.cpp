#include "ssr2/Machine.hpp"

ssr2::Machine::Machine(
    LowerBody &lowerBody,
    Solenoid  &solenoid,
    ForkLift  &forkLift,
    Hand      &hand,
    Arm       &arm,
    PS4USB    &ps4
) : _ps4Value(),
    lowerBody(lowerBody),
    solenoid(solenoid),
    forkLift(forkLift),
    hand(hand),
    arm(arm),
    ps4(ps4)
{}

void ssr2::Machine::update() noexcept {
    ps4.update();
    ps4.read(&_ps4Value);
    hand.update();
    solenoid.update();
}

bool ssr2::Machine::isPS4Connected() const noexcept {
    return ps4.connected();
}

const ssr2::PS4Value & ssr2::Machine::currentPS4Value() const noexcept {
    return _ps4Value;
}
