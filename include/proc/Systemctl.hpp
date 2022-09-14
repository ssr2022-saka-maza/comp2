#pragma once

#include "ssr2/Process.hpp"

namespace proc {
    class Systemctl : public ssr2::Process {
    public:
        virtual void begin(ssr2::Machine *machine) noexcept override;
        virtual void update(ssr2::Machine *machine) noexcept override;
    }; // class Systemctl
} // namespace proc
