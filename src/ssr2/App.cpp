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
}
