#include "proc/Hand.hpp"

void proc::Hand::begin(ssr2::Machine *machine) {
    status = ssr2::ProcessStatus::running;
}

void proc::Hand::update(ssr2::Machine *machine) {
    ssr2::Hand *hand = machine->hand();
    if (hand == nullptr || hand == NULL) {
#ifdef proc_verbose
        Serial.println(F("[proc::Hand] machine->hand is null"));
#endif /* proc_verbose */
        return;
    }
    const ssr2::PS4Value &value = machine->currentPS4Value();
    int16_t angle = hand->read();
    angle += value.l1 - value.r1;
    hand->write(angle);
#ifdef proc_verbose
    char buffer[256] = "";
    snprintf_P(buffer, 200, PSTR("[proc::Hand] set angle as %d\n"), angle);
    Serial.print(buffer);
#endif /* proc_verbose */
}
