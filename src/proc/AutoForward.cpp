#include "proc/AutoForward.hpp"

proc::AutoForward::AutoForward() noexcept
: Process(), _ps4Value(), _step(Step::init), _beginForwardTime(0) {}

void proc::AutoForward::begin(ssr2::Machine *machine) noexcept {
    status = ssr2::ProcessStatus::running;
    _step = Step::init;
}

void proc::AutoForward::update(ssr2::Machine *machine) noexcept {
    const ssr2::PS4Value &value = machine->currentPS4Value();
    #ifdef proc_verbose
    char buffer[256] = "";
    char *ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("[proc::AutoForward] step is "));
    #endif /* proc_verbose */
    switch (_step) {
    case Step::init:
        #ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR("init"));
        #endif /* proc_verbose */
        if (value.options) {
            status = ssr2::ProcessStatus::runningPrior;
            _step = Step::ready;
            #ifdef proc_verbose
            ptr += snprintf_P(ptr, 200, PSTR(", set step as ready"));
            #endif /* proc_verbose */
        }
        break;
    case Step::ready:
        #ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR("ready"));
        #endif /* proc_verbose */
        machine->reset();
        if (!value.options) {
            _step = Step::forward;
            _beginForwardTime = millis();
            _ps4Value = value;
            #ifdef proc_verbose
            ptr += snprintf_P(ptr, 200, PSTR(", set step as forward"));
            #endif /* proc_verbose */
        }
        break;
    case Step::forward:
        #ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR("forward"));
        #endif /* proc_verbose */
        if (_ps4Value != value) {
            status = ssr2::ProcessStatus::running;
            _step = Step::init;
            #ifdef proc_verbose
            ptr += snprintf_P(ptr, 200, PSTR(", set step as init"));
            #endif /* proc_verbose */
            break;
        }
        int64_t dt = millis() - _beginForwardTime;
        if (dt < 1000) {
            #ifdef proc_verbose
            ptr += snprintf_P(ptr, 200, PSTR(", go forward"));
            #endif /* proc_verbose */
            machine->lowerBody.twist(128, 0, 0);
        } else if (dt < 1500) {
            #ifdef proc_verbose
            ptr += snprintf_P(ptr, 200, PSTR(", go backward"));
            #endif /* proc_verbose */
            // 192 = 128 + 64
            machine->lowerBody.twist(-192, 0, 0);
        } else {
            status = ssr2::ProcessStatus::running;
            _step = Step::init;
            #ifdef proc_verbose
            ptr += snprintf_P(ptr, 200, PSTR(", set step as init"));
            #endif /* proc_verbose */
        }
        break;
    }
    #ifdef proc_verbose
    Serial.println(buffer);
    #endif /* proc_verbose */
}
