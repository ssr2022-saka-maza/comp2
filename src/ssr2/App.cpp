#include "ssr2/App.hpp"

ssr2::App::App(Machine *machine) noexcept
: _machine(machine), _processes() {}

void ssr2::App::begin() noexcept {
    _machine->begin();
    for (auto process : _processes) {
        process->begin(_machine);
    }
}

void ssr2::App::update() noexcept {
    _machine->update();
    LimitedVector<Process *, 64> priorProcesses;
    for (auto process : _processes) {
        if (process->status == ProcessStatus::runningPrior) {
            priorProcesses.push_back(process);
        }
    }
    if (priorProcesses.size() > 0) {
        for (auto process : priorProcesses) {
            process->update(_machine);
        }
        return;
    }
    for (auto process : _processes) {
        if (process->status == ProcessStatus::running) {
            process->update(_machine);
        }
    }
}

ssr2::Machine *ssr2::App::machine() noexcept {
    return _machine;
}

const ssr2::Machine *ssr2::App::machine() const noexcept {
    return _machine;
}

void ssr2::App::addProcess(Process *process) noexcept {
    _processes.push_back(process);
    #ifdef SSR_VERBOSE
    char buffer[256] = "";
    snprintf_P(buffer, 256, PSTR("[ssr2::App::addProcess] Added process:  %d"), process->id);
    Serial.print(F("Added process: "));
    Serial.println(process->id);
    #endif /* SSR_VERBOSE */
}
