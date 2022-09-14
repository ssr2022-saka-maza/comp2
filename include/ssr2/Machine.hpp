#pragma once

#include <Arduino.h>
#include "ssr2/LowerBody.hpp"
#include "ssr2/ConstrainedMServo.hpp"
#include "ssr2/Solenoid.hpp"
#include "ssr2/PS4USB.hpp"

namespace ssr2 {
    using ForkLift = ConstrainedMServo;
    using Hand     = ConstrainedMServo;
    using Arm      = ConstrainedMServo;

    class Machine {
    private:
        PS4Value _ps4Value;
    public:
        LowerBody &lowerBody;
        Solenoid  &solenoid;
        ForkLift  &forkLift;
        Hand      &hand;
        Arm       &arm;
        PS4USB    &ps4;

        explicit Machine(
            LowerBody &lowerBody,
            Solenoid  &solenoid,
            ForkLift  &forkLift,
            Hand      &hand,
            Arm       &arm,
            PS4USB    &ps4
        );

        Machine(const Machine &) = delete;
        Machine & operator=(const Machine &) = delete;
        Machine(Machine&&) = delete;
        Machine & operator=(Machine&&) = delete;
        ~Machine() = default;

        virtual void begin() noexcept = 0;
        void update() noexcept;

        bool isPS4Connected() const noexcept;
        const PS4Value & currentPS4Value() const noexcept;
    }; // class Machine
} // namespace ssr2
