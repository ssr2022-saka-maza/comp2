#include "proc/AutoReload.hpp"

proc::AutoReload::AutoReload() noexcept
: Process(), _ps4Value(), _step(Step::init), _beginReloadTime(0) {}

void proc::AutoReload::begin(ssr2::Machine *machine) noexcept {
    status = ssr2::ProcessStatus::running;
    _step = Step::init;
}

void proc::AutoReload::update(ssr2::Machine *machine) noexcept {
    const ssr2::PS4Value &value = machine->currentPS4Value();
    #ifdef proc_verbose
    char buffer[256] = "";
    char *ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("[proc::AutoReload] step is "));
    #endif /* proc_verbose */
    switch (_step) {
    case Step::init:
        #ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR("init"));
        #endif /* proc_verbose */
        if (value.square) {
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
        if (!value.square) {
            _step = Step::reload;
            _beginReloadTime = millis();
            _ps4Value = value;
            #ifdef proc_verbose
            ptr += snprintf_P(ptr, 200, PSTR(", set step as reload"));
            #endif /* proc_verbose */
        }
        break;
    case Step::reload:
        #ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR("reload"));
        #endif /* proc_verbose */
        if (_ps4Value != value) {
            status = ssr2::ProcessStatus::running;
            _step = Step::init;
            #ifdef proc_verbose
            ptr += snprintf_P(ptr, 200, PSTR(", set step as init"));
            #endif /* proc_verbose */
            break;
        }
        int64_t dt = millis() - _beginReloadTime;
        if (dt < 1000) {
            // ハンド: 前に出て開いた状態
            // ハンドを閉じる
            auto &hand = machine->hand;
            hand.write(hand.read() - 1);
            #ifdef proc_verbose
            ptr += snprintf_P(ptr, 200, PSTR(", close hand"));
            #endif /* proc_verbose */
        } else if (dt < 2000) {
            // アームを回転させる
            auto &arm = machine->arm;
            arm.write(arm.read() + 1);
            #ifdef proc_verbose
            ptr += snprintf_P(ptr, 200, PSTR(", rotate arm"));
            #endif /* proc_verbose */
        } else if (dt < 3000) {
            // ハンドを開く
            auto &hand = machine->hand;
            hand.write(hand.read() + 1);
            #ifdef proc_verbose
            ptr += snprintf_P(ptr, 200, PSTR(", open hand"));
            #endif /* proc_verbose */
        } else {
            // done!
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
