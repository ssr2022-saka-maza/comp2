#include "proc/Systemctl.hpp"

void proc::Systemctl::begin(ssr2::Machine *machine) noexcept {
    status = ssr2::ProcessStatus::running;
}

void proc::Systemctl::update(ssr2::Machine *machine) noexcept {
    if (machine->currentPS4Value().ps) {
        machine->reset();
        status = ssr2::ProcessStatus::runningPrior;
    }
}
