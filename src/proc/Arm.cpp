#include "proc/Arm.hpp"

proc::Arm::Arm(Hand *hand, int16_t liftAngle) noexcept : _dAngle(0), _hand(hand), _liftAngle(liftAngle) {}

void proc::Arm::begin(ssr2::Machine *machine) {
    status = ssr2::ProcessStatus::running;
}

void proc::Arm::update(ssr2::Machine *machine) {
    const ssr2::PS4Value &value = machine->currentPS4Value();
    int16_t d = value.triangle - value.cross;
    if (d != 0) {
        _dAngle = d;
    }
    int16_t angle = machine->arm.read();
    machine->arm.write(angle + _dAngle);
    // ハンドの干渉チェック
    if ((_liftAngle - angle) * _dAngle >= 0) {
        // 昇降機構に干渉しそうな方向に動いている
        _hand->status = ssr2::ProcessStatus::stopped;
        int16_t handAngle = machine->hand.read();
        if (handAngle != -1 && handAngle > 80) {
            // 干渉しそう
            machine->hand.write(handAngle - 3);
        }
    } else {
        _hand->status = ssr2::ProcessStatus::running;
    }
}
