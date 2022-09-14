#pragma once

#include <Arduino.h>
#include <Servo.h>
#include "ssr2/MirrorServo.hpp"

namespace ssr2 {
    class ConstrainedMServo : public MirrorServo {
    private:
        int16_t _initialAngle;

    public:
        const int16_t minAngle, maxAngle;

        explicit ConstrainedMServo(int16_t minAngle = 0, int16_t maxAngle = 180);
        void reset() noexcept;
        void begin(int16_t angle = 0) noexcept;
        void write(int16_t angle) noexcept;
    }; // class ConstrainedMServo
} // namespace ssr2
