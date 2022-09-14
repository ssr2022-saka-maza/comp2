#include "ssr2/Process.hpp"

namespace proc {
    class AutoReload : public ssr2::Process {
    private:
        enum class Step : char {
            init,
            ready,
            reload,
        };

        ssr2::PS4Value _ps4Value;
        Step _step;
        uint64_t _beginReloadTime;
    public:
        AutoReload() noexcept;
        AutoReload(const AutoReload &) = delete;
        AutoReload & operator=(const AutoReload &) = delete;
        AutoReload(AutoReload&&) = delete;
        AutoReload & operator=(AutoReload&&) = delete;
        ~AutoReload() = default;

        void begin(ssr2::Machine *machine) noexcept override;
        void update(ssr2::Machine *machine) noexcept override;
    }; // class AutoReload
} // namespace proc
