#include "proc/AutoForward.hpp"

proc::AutoForward::AutoForward() noexcept :
    Process(), _ps4Value(), _step(Step::init), _beginForwardTime(0) {}

void proc::AutoForward::begin(ssr2::Machine *machine) noexcept {
    status = ssr2::ProcessStatus::running;
    _step = Step::init;
}

#ifdef proc_verbose

uint8_t proc::AutoForward::_update_step_init(const ssr2::PS4Value &value,
                                             char *buffer) {
    char *ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("init"));
    if (value.options) {
        status = ssr2::ProcessStatus::runningPrior;
        _step = Step::ready;
        ptr += snprintf_P(ptr, 200, PSTR(", set step as ready"));
    }
    return ptr - buffer;
}

uint8_t proc::AutoForward::_update_step_ready(
    ssr2::Machine *machine, const ssr2::PS4Value &value, char *buffer) {
    char *ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("ready"));
    machine->reset();
    if (!value.options) {
        _step = Step::forward;
        _beginForwardTime = millis();
        _ps4Value = value;
        ptr += snprintf_P(ptr, 200, PSTR(", set step as forward"));
    }
    return ptr - buffer;
}

uint8_t proc::AutoForward::_update_step_forward(
    ssr2::Machine *machine, const ssr2::PS4Value &value, char *buffer) {
    char *ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("forward"));
    if (_ps4Value != value) {
        status = ssr2::ProcessStatus::running;
        _step = Step::init;
        ptr += snprintf_P(ptr, 200, PSTR(", set step as init"));
        return ptr - buffer;
    }
    int64_t dt = millis() - _beginForwardTime;
    ssr2::LowerBody *lowerBody = machine->lowerBody_();
    if (lowerBody == nullptr || lowerBody == NULL) {
        return ptr - buffer;
    }
    if (dt < 1000) {
        ptr += snprintf_P(ptr, 200, PSTR(", go forward"));
        lowerBody->twist(128, 0, 0);
    } else if (dt < 1500) {
        ptr += snprintf_P(ptr, 200, PSTR(", go backward"));
        // 192 = 128 + 64
        lowerBody->twist(-192, 0, 0);
    } else {
        status = ssr2::ProcessStatus::running;
        _step = Step::init;
        ptr += snprintf_P(ptr, 200, PSTR(", set step as init"));
    }
    return ptr - buffer;
}

#else /* proc_verbose */

void proc::AutoForward::_update_step_init(const ssr2::PS4Value &value) {
    if (value.options) {
        status = ssr2::ProcessStatus::runningPrior;
        _step = Step::ready;
    }
}

void proc::AutoForward::_update_step_ready(ssr2::Machine *machine,
                                           const ssr2::PS4Value &value) {
    machine->reset();
    if (!value.options) {
        _step = Step::forward;
        _beginForwardTime = millis();
        _ps4Value = value;
    }
}

void proc::AutoForward::_update_step_forward(ssr2::Machine *machine,
                                             const ssr2::PS4Value &value) {
    if (_ps4Value != value) {
        status = ssr2::ProcessStatus::running;
        _step = Step::init;
        return;
    }
    int64_t dt = millis() - _beginForwardTime;
    ssr2::LowerBody *lowerBody = machine->lowerBody_();
    if (lowerBody == nullptr || lowerBody == NULL) {
        return;
    }
    if (dt < 1000) {
        lowerBody->twist(128, 0, 0);
    } else if (dt < 1500) {
        // 192 = 128 + 64
        lowerBody->twist(-192, 0, 0);
    } else {
        status = ssr2::ProcessStatus::running;
        _step = Step::init;
    }
}

#endif /* proc_verbose */

void proc::AutoForward::update(ssr2::Machine *machine) noexcept {
    const ssr2::PS4Value &value = machine->currentPS4Value();
#ifdef proc_verbose
    char buffer[256] = "";
    char *ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("[proc::AutoForward] step is "));
    switch (_step) {
    case Step::init:
        ptr += _update_step_init(value, ptr);
        break;
    case Step::ready:
        ptr += _update_step_ready(machine, value, ptr);
        break;
    case Step::forward:
        ptr += _update_step_forward(machine, value, ptr);
        break;
    }
    Serial.println(buffer);
#else  /* proc_verbose */
    switch (_step) {
    case Step::init:
        _update_step_init(value);
        break;
    case Step::ready:
        _update_step_ready(machine, value);
        break;
    case Step::forward:
        _update_step_forward(machine, value);
        break;
    }
#endif /* proc_verbose */
}
