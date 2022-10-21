#include "proc/PS4Log.hpp"

void proc::PS4Log::begin(ssr2::Machine *machine) {
    Process::status = ssr2::ProcessStatus::running;
}

void proc::PS4Log::update(ssr2::Machine *machine) {
#ifdef proc_verbose
    Serial.print(F("[proc::PS4Log] update\n"));
#endif /* proc_verbose */
    if (machine->isPS4Connected()) {
        const ssr2::PS4Value &value = machine->currentPS4Value();
        char log[256] = "";
        sprintf_P(
            log,
            PSTR("(%#x %#x) (%#x %#x) [%d %d %d %d] [%d %d %d %d] [%d %d %d] [%d %#x %d] [%d %#x %d]\n"),
            value.lstick.x, value.lstick.y,
            value.rstick.x, value.rstick.y,
            value.up, value.right, value.down, value.left,
            value.triangle, value.circle, value.cross, value.square,
            value.ps, value.share, value.options,
            value.l1, value.l2, value.l3,
            value.r1, value.r2, value.r3);
        Serial.print(log);
    } else {
        Serial.println(F("PS4 is not connected"));
    }
}
