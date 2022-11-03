#include <Arduino.h>

#include <ssr2/App.hpp>

#include <proc/Arm.hpp>
#include <proc/AutoForward.hpp>
#include <proc/AutoReload.hpp>
#include <proc/ForkLift.hpp>
#include <proc/Hand.hpp>
#include <proc/LowerBody.hpp>
#include <proc/NeoPixel.hpp>
#include <proc/PS4Log.hpp>
#include <proc/Solenoid.hpp>
#include <proc/Systemctl.hpp>

#include <MainMachine.hpp>

MainMachine machine{};
ssr2::App app(&machine);

void setup() {
    Serial.begin(115200);
    // app.addProcess(new proc::PS4Log());
    app.addProcess(new proc::LowerBody());
    proc::Hand * hand = new proc::Hand();
    app.addProcess(hand);
    app.addProcess(new proc::ForkLift());
    // app.addProcess(new proc::Solenoid(hand));
    app.addProcess(new proc::Arm(hand));
    // app.addProcess(new proc::AutoForward());
    app.addProcess(new proc::NeoPixel());
    // app.addProcess(new proc::Systemctl());
    // app.addProcess(new proc::AutoReload());
    app.begin();
}

void loop() {
    app.update();
}
