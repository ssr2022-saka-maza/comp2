#include "proc/Arm.hpp"

proc::Arm::Arm(Hand *hand, int16_t liftAngle) noexcept
    : _dAngle(0), _hand(hand), _liftAngle(liftAngle) {}

void proc::Arm::begin(ssr2::Machine *machine) {
    status = ssr2::ProcessStatus::running;
}

void proc::Arm::update(ssr2::Machine *machine) {
    const ssr2::PS4Value &value = machine->currentPS4Value();
    int16_t d = value.triangle - value.cross;
    if (d != 0) {
        _dAngle = d;
    }
    ssr2::Arm *arm = machine->arm_();
    if (arm == nullptr || arm == NULL) {
        return;
    }
    int16_t angle = arm->read();
    arm->write(angle + _dAngle);
    ssr2::Hand *machine_hand = machine->hand_();
    if (machine_hand == nullptr || machine_hand == NULL) {
        return;
    }
#ifdef proc_verbose
    char buffer[256] = "";
    char *ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("[proc::Arm] set angle as %d"), angle);
#endif /* proc_verbose */
    // ハンドの干渉チェック
    if ((_liftAngle - angle) * _dAngle > 0) {
        // 昇降機構に干渉しそうな方向に動いている
        _hand->status = ssr2::ProcessStatus::stopped;
        int16_t handAngle = machine_hand->read();
#ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR(", stopped hand process"));
#endif /* proc_verbose */
        if (handAngle != -1 && handAngle > 80) {
            // 干渉しそう
            machine_hand->write(handAngle - 5);
#ifdef proc_verbose
            ptr += snprintf_P(ptr, 200, PSTR(", set hand angle as %d"), handAngle - 5);
#endif /* proc_verbose */
        }
    } else {
        _hand->status = ssr2::ProcessStatus::running;
#ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR(", run hand process"));
#endif /* proc_verbose */
    }
#ifdef proc_verbose
    Serial.println(buffer);
#endif /* proc_verbose */
}
