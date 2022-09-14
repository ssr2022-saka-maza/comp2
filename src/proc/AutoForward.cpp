#include "proc/AutoForward.hpp"

proc::AutoForward::AutoForward() noexcept
: Process(), _ps4Value(), _step(Step::init), _beginForwardTime(0) {}

void proc::AutoForward::begin(ssr2::Machine *machine) noexcept {
    status = ssr2::ProcessStatus::running;
    _step = Step::init;
}

void proc::AutoForward::update(ssr2::Machine *machine) noexcept {
    const ssr2::PS4Value &value = machine->currentPS4Value();
    switch (_step) {
    case Step::init:
        if (value.options) {
            status = ssr2::ProcessStatus::runningPrior;
            _step = Step::ready;
        }
        break;
    case Step::ready:
        machine->reset();
        if (!value.options) {
            _step = Step::forward;
            _beginForwardTime = millis();
            _ps4Value = value;
        }
        break;
    case Step::forward:
        if (_ps4Value != value) {
            status = ssr2::ProcessStatus::running;
            _step = Step::init;
            return;
        }
        int64_t dt = millis() - _beginForwardTime;
        if (dt < 1000) {
            machine->lowerBody.twist(128, 0, 0);
        } else if (dt < 1500) {
            // 192 = 128 + 64
            machine->lowerBody.twist(-192, 0, 0);
        } else {
            status = ssr2::ProcessStatus::running;
            _step = Step::init;
        }
        break;
    }
}
