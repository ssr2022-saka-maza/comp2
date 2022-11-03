#pragma once

#include "ssr2/Machine.hpp"
#include "ssr2/Process.hpp"
#include <Arduino.h>

namespace proc {

class LowerBody : public ssr2::Process {
private:
    static const float _sqrt2;

    static float _mapPower(uint8_t value) noexcept;

public:
    virtual void begin(ssr2::Machine * machine) override;
    virtual void update(ssr2::Machine * machine) override;
};  // class LowerBody

}  // namespace proc
