#include "proc/AutoReload.hpp"

proc::AutoReload::AutoReload() noexcept
    : Process(), _ps4Value(), _step(Step::init), _beginReloadTime(0) {}

void proc::AutoReload::begin(ssr2::Machine *machine) noexcept {
    status = ssr2::ProcessStatus::running;
    _step = Step::init;
}

#ifdef proc_verbose

uint8_t proc::AutoReload::_update_step_init(const ssr2::PS4Value &value, char *buffer) {
    char *ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("init"));
    if (value.square) {
        status = ssr2::ProcessStatus::runningPrior;
        _step = Step::ready;
        ptr += snprintf_P(ptr, 200, PSTR(", set step as ready"));
    }
    return ptr - buffer;
}

uint8_t proc::AutoReload::_update_step_ready(ssr2::Machine *machine, const ssr2::PS4Value &value, char *buffer) {
    char *ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("ready"));
    machine->reset();
    if (!value.square) {
        _step = Step::reload;
        _beginReloadTime = millis();
        _ps4Value = value;
        ptr += snprintf_P(ptr, 200, PSTR(", set step as reload"));
    }
    return ptr - buffer;
}

uint8_t proc::AutoReload::_update_step_reload(ssr2::Machine *machine, const ssr2::PS4Value &value, char *buffer) {
    char *ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("reload"));
    if (_ps4Value != value) {
        status = ssr2::ProcessStatus::running;
        _step = Step::init;
        ptr += snprintf_P(ptr, 200, PSTR(", set step as init"));
        return ptr - buffer;
    }
    // get hand
    ssr2::Hand *hand = machine->hand_();
    if (hand == nullptr || hand == NULL) {
        return ptr - buffer;
    }
    // get arm
    ssr2::Arm *arm = machine->arm_();
    if (arm == nullptr || arm == NULL) {
        return ptr - buffer;
    }
    int64_t dt = millis() - _beginReloadTime;
    if (dt < 1000) {
        // ハンド: 前に出て開いた状態
        // ハンドを閉じる
        hand->write(hand->read() - 1);
        ptr += snprintf_P(ptr, 200, PSTR(", close hand"));
    } else if (dt < 2000) {
        // アームを回転させる
        arm->write(arm->read() + 1);
        ptr += snprintf_P(ptr, 200, PSTR(", rotate arm"));
    } else if (dt < 3000) {
        // ハンドを開く
        hand->write(hand->read() + 1);
        ptr += snprintf_P(ptr, 200, PSTR(", open hand"));
    } else {
        // done!
        status = ssr2::ProcessStatus::running;
        _step = Step::init;
        ptr += snprintf_P(ptr, 200, PSTR(", set step as init"));
    }
    return ptr - buffer;
}

#else /* proc_verbose */

void proc::AutoReload::_update_step_init(const ssr2::PS4Value &value) {
    if (value.square) {
        status = ssr2::ProcessStatus::runningPrior;
        _step = Step::ready;
    }
}

void proc::AutoReload::_update_step_ready(ssr2::Machine *machine, const ssr2::PS4Value &value) {
    machine->reset();
    if (!value.square) {
        _step = Step::reload;
        _beginReloadTime = millis();
        _ps4Value = value;
    }
}

void proc::AutoReload::_update_step_reload(ssr2::Machine *machine, const ssr2::PS4Value &value) {
    if (_ps4Value != value) {
        status = ssr2::ProcessStatus::running;
        _step = Step::init;
    }
    // get hand
    ssr2::Hand *hand = machine->hand_();
    if (hand == nullptr || hand == NULL) {
        return;
    }
    // get arm
    ssr2::Arm *arm = machine->arm_();
    if (arm == nullptr || arm == NULL) {
        return;
    }
    int64_t dt = millis() - _beginReloadTime;
    if (dt < 1000) {
        // ハンド: 前に出て開いた状態
        // ハンドを閉じる
        hand->write(hand->read() - 1);
    } else if (dt < 2000) {
        // アームを回転させる
        arm->write(arm->read() + 1);
    } else if (dt < 3000) {
        // ハンドを開く
        hand->write(hand->read() + 1);
    } else {
        // done!
        status = ssr2::ProcessStatus::running;
        _step = Step::init;
    }
}

#endif /* proc_verbose */

void proc::AutoReload::update(ssr2::Machine *machine) noexcept {
    const ssr2::PS4Value &value = machine->currentPS4Value();
#ifdef proc_verbose
    char buffer[256] = "";
    char *ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("[proc::AutoReload] step is "));
    switch (_step) {
    case Step::init:
        ptr += _update_step_init(value, ptr);
        break;
    case Step::ready:
        ptr += _update_step_ready(machine, value, ptr);
        break;
    case Step::reload:
        ptr += _update_step_reload(machine, value, ptr);
        break; // Step::reload
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
    case Step::reload:
        _update_step_reload(machine, value);
        break; // Step::reload
    }
#endif /* proc_verbose */
}
