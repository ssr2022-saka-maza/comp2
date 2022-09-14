#pragma once

#include "ssr2/Machine.hpp"

namespace ssr2 {
    class Process {
    public:
        virtual void begin() noexcept = 0;
        virtual void update(Machine *machine) noexcept = 0;
    }; // class Process
} // namespace ssr2
