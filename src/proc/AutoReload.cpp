#include "proc/AutoReload.hpp"

proc::AutoReload::AutoReload() noexcept
: Process(), _ps4Value(), _step(Step::init), _beginReloadTime(0) {}

void proc::AutoReload::begin(ssr2::Machine *machine) noexcept {
    status = ssr2::ProcessStatus::running;
    _step = Step::init;
}

void proc::AutoReload::update(ssr2::Machine *machine) noexcept {
    const ssr2::PS4Value &value = machine->currentPS4Value();
    switch (_step) {
    case Step::init:
        if (value.square) {
            status = ssr2::ProcessStatus::runningPrior;
            _step = Step::ready;
        }
        break;
    case Step::ready:
        machine->reset();
        if (!value.square) {
            _step = Step::reload;
            _beginReloadTime = millis();
            _ps4Value = value;
        }
        break;
    case Step::reload:
        if (_ps4Value != value) {
            status = ssr2::ProcessStatus::running;
            _step = Step::init;
            return;
        }
        int64_t dt = millis() - _beginReloadTime;
        if (dt < 1000) {
            // ハンド: 前に出て開いた状態
            // ハンドを閉じる
            auto &hand = machine->hand;
            hand.write(hand.read() - 1);
        } else if (dt < 2000) {
            // アームを回転させる
            auto &arm = machine->arm;
            arm.write(arm.read() + 1);
        } else if (dt < 3000) {
            // ハンドを開く
            auto &hand = machine->hand;
            hand.write(hand.read() + 1);
        } else {
            // done!
            status = ssr2::ProcessStatus::running;
            _step = Step::init;
        }
        break;
    }
}
