#pragma once

#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

#include <ssr2/Hand.hpp>
#include <ssr2/LowerBody.hpp>
#include <ssr2/Machine.hpp>
#include <ssr2/Solenoid.hpp>

class MainMachine : public ssr2::Machine {
    ssr2::LowerBody _lowerBody;
    ssr2::Solenoid _solenoid;
    ssr2::ForkLift _forkLift;
    ssr2::Hand _hand;
    ssr2::Arm _arm;
    ssr2::PS4USB _ps4;
    Adafruit_NeoPixel _pixels;

public:
    explicit MainMachine();

    virtual void begin() noexcept override;

    virtual ssr2::LowerBody *lowerBody() override;
    virtual ssr2::Solenoid *solenoid() override;
    virtual ssr2::ForkLift *forkLift() override;
    virtual ssr2::Hand *hand() override;
    virtual ssr2::Arm *arm() override;
    virtual ssr2::PS4USB *ps4() override;
    virtual Adafruit_NeoPixel *pixels() override;
};
