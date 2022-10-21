#pragma once

#include "proc/Hand.hpp"
#include "ssr2/Process.hpp"

namespace proc {

class Solenoid : public ssr2::Process {
private:
    Hand *_hand;
    bool _requested;

    bool _canFire(ssr2::Solenoid *machineSolenoid, ssr2::Arm *machineArm, ssr2::Hand *machineHand) const noexcept;

public:
    Solenoid() = delete;
    ~Solenoid() = default;

    explicit Solenoid(Hand *hand) noexcept;

    virtual void begin(ssr2::Machine *machine) override;
    virtual void update(ssr2::Machine *machine) override;
}; // class Solenoid

} // namespace proc
