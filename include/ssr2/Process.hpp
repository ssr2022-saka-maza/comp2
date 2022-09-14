#pragma once

#include "ssr2/ProcessStatus.hpp"
#include "ssr2/Machine.hpp"

namespace ssr2 {
    class Process {
    private:
        static uint32_t _genId() noexcept;

    public:
        const uint32_t id;
        ProcessStatus status;

        explicit Process() noexcept;

        virtual void begin() = 0;
        virtual void update(Machine *machine) = 0;
    }; // class Process
} // namespace ssr2
