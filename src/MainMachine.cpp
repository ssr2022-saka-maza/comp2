#include "MainMachine.hpp"

MainMachine::MainMachine() :
    _lowerBody(6, 7, 4, 5, 2, 3, 64), _solenoid(A8, 100), _forkLift(0, 180),
    _hand(70, 110), _arm(0, 150), _ps4() {}

void MainMachine::begin() {
    /* PWM frequency */
    // pin:   7, 5, 3
    // timer: 4, 3, 3
    TCCR3B = (TCCR3B & 0b11111000) | 0x02; // Timer3 3.92116[kHz]
    TCCR4B = (TCCR4B & 0b11111000) | 0x02; // Timer4 3.92116[kHz]
    _forkLift.attach(23, 25);
    _hand.attach(27, 29);
    _arm.attach(31, 33);
    _forkLift.begin(0);
    _hand.begin(70);
    _arm.begin(140);
    if (_ps4.begin() == -1) {
        Serial.println("PS4USB::begin() failed.");
    }
    _lowerBody.begin();
}

ssr2::LowerBody *MainMachine::lowerBody_() { return &_lowerBody; }

ssr2::Solenoid *MainMachine::solenoid_() { return &_solenoid; }

ssr2::ForkLift *MainMachine::forkLift_() { return &_forkLift; }

ssr2::Hand *MainMachine::hand_() { return &_hand; }

ssr2::Arm *MainMachine::arm_() { return &_arm; }

ssr2::PS4USB *MainMachine::ps4_() { return &_ps4; }
