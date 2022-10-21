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
#ifdef ssr2_verbose
    char buffer[256] = "";
    char *ptr = buffer;
    ptr += snprintf_P(buffer, 255, PSTR("[ssr2::App] update"));
#endif /* ssr2_verbose */
    LimitedVector<Process *, 64> priorProcesses;
    for (auto process : _processes) {
        if (process->status == ProcessStatus::runningPrior) {
            priorProcesses.push_back(process);
        }
    }
    if (priorProcesses.size() > 0) {
        for (auto process : priorProcesses) {
            process->update(_machine);
#ifdef ssr2_verbose
            ptr += snprintf_P(ptr, 255 - (ptr - buffer), PSTR(" %d"), process->id);
#endif /* ssr2_verbose */
        }
    } else {
        for (auto process : _processes) {
            if (process->status == ProcessStatus::running) {
                process->update(_machine);
#ifdef ssr2_verbose
                ptr += snprintf_P(ptr, 255 - (ptr - buffer), PSTR(" %d"), process->id);
#endif /* ssr2_verbose */
            }
        }
    }
#ifdef ssr2_verbose
    Serial.println(buffer);
#endif /* ssr2_verbose */
}

ssr2::Machine *ssr2::App::machine() noexcept {
    return _machine;
}

void ssr2::App::addProcess(Process *process) noexcept {
    _processes.push_back(process);
}
