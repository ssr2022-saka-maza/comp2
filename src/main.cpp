#include <Arduino.h>
#include <proc/Arm.hpp>
#include <proc/AutoForward.hpp>
#include <proc/AutoReload.hpp>
#include <proc/ForkLift.hpp>
#include <proc/Hand.hpp>
#include <proc/LowerBody.hpp>
#include <proc/PS4Log.hpp>
#include <proc/Solenoid.hpp>
#include <proc/Systemctl.hpp>
#include <ssr2/App.hpp>

class MainMachine : public ssr2::Machine {
    ssr2::LowerBody _lowerBody;
    ssr2::Solenoid _solenoid;
    ssr2::ForkLift _forkLift;
    ssr2::Hand _hand;
    ssr2::Arm _arm;
    ssr2::PS4USB _ps4;

public:
    explicit MainMachine()
        : _lowerBody(6, 7, 4, 5, 2, 3, 64), _solenoid(A8, 100),
          _forkLift(0, 180), _hand(70, 110), _arm(0, 150), _ps4() {}

    virtual void begin() noexcept override {
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

    virtual ssr2::LowerBody *lowerBody_() override { return &_lowerBody; }
    virtual ssr2::Solenoid *solenoid_() override { return &_solenoid; }
    virtual ssr2::ForkLift *forkLift_() override { return &_forkLift; }
    virtual ssr2::Hand *hand_() override { return &_hand; }
    virtual ssr2::Arm *arm_() override { return &_arm; }
    virtual ssr2::PS4USB *ps4_() override { return &_ps4; }
};

MainMachine machine{};
ssr2::App app(&machine);

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
    // app.addProcess(new proc::Systemctl());
    // app.addProcess(new proc::AutoReload());
    app.begin();
}

void loop() { app.update(); }
