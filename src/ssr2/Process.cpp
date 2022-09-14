#include "ssr2/Process.hpp"

uint32_t ssr2::Process::_genId() noexcept {
    static uint32_t id = 0;
    return id++;
}

ssr2::Process::Process() noexcept : id(_genId()), status(ssr2::ProcessStatus::stopped) {}
