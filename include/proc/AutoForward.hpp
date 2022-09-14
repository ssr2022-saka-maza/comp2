#pragma once

#include "ssr2/Process.hpp"

namespace proc {
    class AutoForward : public ssr2::Process {
    private:
        enum class Step : char {
            init,
            ready,
            forward,
        };

        ssr2::PS4Value _ps4Value;
        Step _step;
        uint64_t _beginForwardTime;
    public:
        AutoForward() noexcept;
        AutoForward(const AutoForward &) = delete;
        AutoForward & operator=(const AutoForward &) = delete;
        AutoForward(AutoForward&&) = delete;
        AutoForward & operator=(AutoForward&&) = delete;
        ~AutoForward() = default;

        void begin(ssr2::Machine *machine) noexcept override;
        void update(ssr2::Machine *machine) noexcept override;
    }; // class AutoForward
} // namespace proc
