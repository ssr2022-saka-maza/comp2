#pragma once

#include "ssr2/ConstrainedMServo.hpp"

namespace ssr2 {

class Hand : public ConstrainedMServo {
private:
    int16_t _angle;

public:
    explicit Hand(int16_t minAngle = 0, int16_t maxAngle = 180);
    void write(int16_t angle) noexcept;
    int16_t read() noexcept;
    void begin(int16_t angle = 0) noexcept;
    void update() noexcept;
};  // class Hand

}  // namespace ssr2
