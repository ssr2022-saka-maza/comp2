#include "proc/Systemctl.hpp"

void proc::Systemctl::begin(ssr2::Machine * machine) noexcept {
    status = ssr2::ProcessStatus::running;
}

void proc::Systemctl::update(ssr2::Machine * machine) noexcept {
#ifdef proc_verbose
    char buffer[256] = "";
    char * ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("[proc::Systemctl] "));
#endif /* proc_verbose */
    if (machine->currentPS4Value().ps) {
        machine->reset();
        status = ssr2::ProcessStatus::runningPrior;
#ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR("reset"));
#endif /* proc_verbose */
    }
#ifdef proc_verbose
    else {
        ptr += snprintf_P(ptr, 200, PSTR("do nothing"));
    }
#endif /* proc_verbose */
#ifdef proc_verbose
    Serial.println(buffer);
#endif /* proc_verbose */
}
