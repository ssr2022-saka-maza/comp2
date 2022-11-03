#include "proc/ForkLift.hpp"

void proc::ForkLift::begin(ssr2::Machine * machine) {
    status = ssr2::ProcessStatus::running;
}

void proc::ForkLift::update(ssr2::Machine * machine) {
    ssr2::ForkLift * machineForkLift = machine->forkLift();
    if (machineForkLift == nullptr || machineForkLift == NULL) {
#ifdef proc_verbose
        Serial.println(F("[proc::ForkLift] machine->forkLift is null"));
#endif /* proc_verbose */
        return;
    }
    const ssr2::PS4Value & value = machine->currentPS4Value();
    int16_t angle = machineForkLift->read();
    int16_t delta = value.up - value.down;
    if (delta == 0) {
#ifdef proc_verbose
        Serial.println(F("[proc::ForkLift] no change"));
#endif /* proc_verbose */
        return;
    }
    angle += delta;
    machineForkLift->write(angle);
#ifdef proc_verbose
    char buffer[256] = "";
    snprintf_P(buffer, 200, PSTR("[proc::ForkLift] set angle as %d\n"), angle);
    Serial.print(buffer);
#endif /* proc_verbose */
}
