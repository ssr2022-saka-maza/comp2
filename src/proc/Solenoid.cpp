#include "proc/Solenoid.hpp"

bool proc::Solenoid::_canFire(ssr2::Machine *machine) const noexcept {
    // ソレノイドが発射してから十分に時間が経っているかどうか
    if (machine->solenoid.isFired()) return false;
    // アーム、ハンドが弾道に干渉しているかどうか
    int armAngle = machine->arm.read();
    if (armAngle != -1 && armAngle <= 110) {
        // アームが十分に弾道から離れた位置にある
        return true;
    }
    int handAngle = machine->hand.read();
    if (handAngle != -1 && handAngle >= 75) {
        // ハンドが十分に弾道から離れた位置にある
        return true;
    }
    return false;
}

proc::Solenoid::Solenoid(Hand *hand) noexcept : _hand(hand) {}

void proc::Solenoid::begin(ssr2::Machine *machine) {
    status = ssr2::ProcessStatus::running;
}

void proc::Solenoid::update(ssr2::Machine *machine) {
    #ifdef proc_verbose
    char buffer[256] = "";
    char *ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("[proc::Solenoid] "));
    #endif /* proc_verbose */
    const ssr2::PS4Value &value = machine->currentPS4Value();
    if (!value.circle) {
        // ソレノイドを発射しない
        #ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR("do nothing"));
        #endif /* proc_verbose */
        goto end;
    }
    _hand->status = ssr2::ProcessStatus::stopped;
    #ifdef proc_verbose
    ptr += snprintf_P(ptr, 200, PSTR("stop hand"));
    #endif /* proc_verbose */
    if (_canFire(machine)) {
        machine->solenoid.fire();
        _hand->status = ssr2::ProcessStatus::running;
        #ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR(", fire solenoid"));
        #endif /* proc_verbose */
    } else {
        // 発射できないので、まずはハンドを開く
        int16_t handAngle = machine->hand.read();
        machine->hand.write(handAngle + 3);
        #ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR(", open hand"));
        #endif /* proc_verbose */
    }
end:
    #ifdef proc_verbose
    Serial.println(buffer);
    #endif /* proc_verbose */
}
