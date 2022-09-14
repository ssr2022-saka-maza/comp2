#include <Arduino.h>
#include <ssr2/App.hpp>
#include <proc/PS4Log.hpp>
#include <proc/LowerBody.hpp>
#include <proc/Hand.hpp>
#include <proc/ForkLift.hpp>
#include <proc/Solenoid.hpp>
#include <proc/Arm.hpp>
#include <proc/AutoForward.hpp>
#include <proc/Systemctl.hpp>

class MainMachine : public ssr2::Machine {
public:
    explicit MainMachine(
        ssr2::LowerBody &lowerBody,
        ssr2::Solenoid  &solenoid,
        ssr2::ForkLift  &forkLift,
        ssr2::Hand      &hand,
        ssr2::Arm       &arm,
        ssr2::PS4USB    &ps4
    ) : ssr2::Machine(lowerBody, solenoid, forkLift, hand, arm, ps4) {}

    virtual void begin() noexcept override {
        /* PWM frequency */
        // pin:   7, 5, 3
        // timer: 4, 3, 3
        TCCR3B = (TCCR3B & 0b11111000) | 0x02; // Timer3 3.92116[kHz]
        TCCR4B = (TCCR4B & 0b11111000) | 0x02; // Timer4 3.92116[kHz]
        forkLift.attach(23, 25);
        hand.attach(27, 29);
        arm.attach(31, 33);
        forkLift.begin(90);
        hand.begin(70);
        arm.begin(100);
        if (ps4.begin() == -1) {
            Serial.println("PS4USB::begin() failed.");
        }
        lowerBody.begin();
    }
};

ssr2::LowerBody lowerBody(6, 7, 4, 5, 2, 3);
ssr2::Solenoid  solenoid(A8);
ssr2::ForkLift  forkLift(0, 180);
ssr2::Hand      hand(70, 110);
ssr2::Arm       arm(0, 150);
ssr2::PS4USB    ps4;
MainMachine     machine(lowerBody, solenoid, forkLift, hand, arm, ps4);
ssr2::App       app(&machine);

void setup() {
    Serial.begin(115200);
    app.addProcess(new proc::PS4Log());
    app.addProcess(new proc::LowerBody());
    proc::Hand *hand = new proc::Hand();
    app.addProcess(hand);
    app.addProcess(new proc::ForkLift());
    app.addProcess(new proc::Solenoid(hand));
    app.addProcess(new proc::Arm(hand));
    app.addProcess(new proc::AutoForward());
    app.addProcess(new proc::Systemctl());
    app.begin();
}

void loop() {
    app.update();
}

