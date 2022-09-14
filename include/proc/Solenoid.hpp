#pragma once

#include "ssr2/Process.hpp"
#include "proc/Hand.hpp"

namespace proc {
    class Solenoid : public ssr2::Process {
    private:
        Hand *_hand;

        bool _canFire(ssr2::Machine *machine) const noexcept;

    public:
        Solenoid() = delete;
        ~Solenoid() = default;

        explicit Solenoid(Hand *hand) noexcept;

        virtual void begin(ssr2::Machine *machine) override;
        virtual void update(ssr2::Machine *machine) override;
    }; // class Solenoid
} // namespace proc
