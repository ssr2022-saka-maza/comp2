#pragma once

#include <Arduino.h>
#include <Servo.h>
#include "ssr2/MirrorServo.hpp"

namespace ssr2 {
    class ConstrainedMServo : public MirrorServo {
    public:
        const uint8_t minAngle, maxAngle;

        explicit ConstrainedMServo(uint8_t minAngle = 0, uint8_t maxAngle = 180);
        void begin(uint8_t angle = 0) noexcept;
        void write(uint8_t angle) noexcept;
    }; // class ConstrainedMServo
} // namespace ssr2
