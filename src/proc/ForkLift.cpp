#include "proc/ForkLift.hpp"

void proc::ForkLift::begin(ssr2::Machine *machine) {
    status = ssr2::ProcessStatus::running;
}

void proc::ForkLift::update(ssr2::Machine *machine) {
    const ssr2::PS4Value &value = machine->currentPS4Value();
    uint8_t angle = machine->forkLift.read();
    angle += value.up - value.down;
    machine->forkLift.write(angle);
}
