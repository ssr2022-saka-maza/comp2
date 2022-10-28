#pragma once

#include "ssr2/ConstrainedMServo.hpp"
#include "ssr2/Hand.hpp"
#include "ssr2/LowerBody.hpp"
#include "ssr2/PS4USB.hpp"
#include "ssr2/Solenoid.hpp"
#include <Arduino.h>

namespace ssr2 {

using ForkLift = ConstrainedMServo;
using Arm = ConstrainedMServo;

class Machine {
private:
    PS4Value _ps4Value;

public:
    explicit Machine();

    Machine(const Machine &) = delete;
    Machine &operator=(const Machine &) = delete;
    Machine(Machine &&) = delete;
    Machine &operator=(Machine &&) = delete;
    ~Machine() = default;

    virtual void begin() noexcept = 0;
    void update() noexcept;
    void reset() noexcept;

    virtual LowerBody *lowerBody() = 0;
    virtual Solenoid *solenoid() = 0;
    virtual ForkLift *forkLift() = 0;
    virtual Hand *hand() = 0;
    virtual Arm *arm() = 0;
    virtual PS4USB *ps4() = 0;

    bool isPS4Connected() noexcept;
    const PS4Value &currentPS4Value() const noexcept;
}; // class Machine

} // namespace ssr2
