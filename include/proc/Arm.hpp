#pragma once

#include "proc/Hand.hpp"
#include "ssr2/Process.hpp"

namespace proc {

class Arm : public ssr2::Process {
private:
    int16_t _dAngle;
    Hand * _hand;
    // 昇降機構に干渉しそうな角度
    const int16_t _liftAngle;

public:
    Arm() = delete;
    ~Arm() = default;

    explicit Arm(Hand * hand, int16_t liftAngle = 100) noexcept;
    virtual void begin(ssr2::Machine * machine) override;
    virtual void update(ssr2::Machine * machine) override;
};  // class Arm

}  // namespace proc
