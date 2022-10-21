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

#ifdef proc_verbose
    uint8_t _update_step_init(const ssr2::PS4Value &value, char *buffer);
    uint8_t _update_step_ready(ssr2::Machine *machine, const ssr2::PS4Value &value, char *buffer);
    uint8_t _update_step_reload(ssr2::Machine *machine, const ssr2::PS4Value &value, char *buffer);
#else  /* proc_verbose */
    void _update_step_init(const ssr2::PS4Value &value);
    void _update_step_ready(ssr2::Machine *machine, const ssr2::PS4Value &value);
    void _update_step_reload(ssr2::Machine *machine, const ssr2::PS4Value &value);
#endif /* proc_verbose */

public:
    AutoReload() noexcept;
    AutoReload(const AutoReload &) = delete;
    AutoReload &operator=(const AutoReload &) = delete;
    AutoReload(AutoReload &&) = delete;
    AutoReload &operator=(AutoReload &&) = delete;
    ~AutoReload() = default;

    void begin(ssr2::Machine *machine) noexcept override;
    void update(ssr2::Machine *machine) noexcept override;
}; // class AutoReload

} // namespace proc
