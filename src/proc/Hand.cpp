#include "proc/Hand.hpp"

void proc::Hand::begin(ssr2::Machine *machine) {
    status = ssr2::ProcessStatus::running;
}

void proc::Hand::update(ssr2::Machine *machine) {
    const ssr2::PS4Value &value = machine->currentPS4Value();
    uint8_t angle = machine->hand.read();
    angle += value.l1 - value.r1;
    machine->hand.write(angle);
}
