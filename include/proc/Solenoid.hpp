#pragma once

#include "ssr2/Process.hpp"

namespace proc {
    class Solenoid : public ssr2::Process {
    private:
        bool _canFire(ssr2::Machine *machine) const noexcept;

    public:
        virtual void begin(ssr2::Machine *machine) override;
        virtual void update(ssr2::Machine *machine) override;
    }; // class Solenoid
} // namespace proc
