#include "proc/Solenoid.hpp"

bool proc::Solenoid::_canFire(ssr2::Solenoid *machineSolenoid, ssr2::Arm *machineArm, ssr2::Hand *machineHand) const noexcept {
    // ソレノイドが発射してから十分に時間が経っているかどうか
    if (machineSolenoid->isFired())
        return false;
    // アーム、ハンドが弾道に干渉しているかどうか
    int armAngle = machineArm->read();
    if (armAngle != -1 && armAngle <= 110) {
        // アームが十分に弾道から離れた位置にある
        return true;
    }
    int handAngle = machineHand->read();
    if (handAngle != -1 && handAngle >= 80) {
        // ハンドが十分に弾道から離れた位置にある
        return true;
    }
    return false;
}

proc::Solenoid::Solenoid(Hand *hand) noexcept : _hand(hand), _requested(false) {}

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
    if (!value.circle && !_requested) {
// ソレノイドを発射しない
#ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR("do nothing"));
        goto end;
#else  /* proc_verbose */
        return;
#endif /* proc_verbose */
    }
    ssr2::Solenoid *machineSolenoid = machine->solenoid_();
    if (machineSolenoid == nullptr || machineSolenoid == NULL) {
#ifdef proc_verbose
        Serial.println(F("[proc::Solenoid] machine->solenoid_ is null"));
#endif /* proc_verbose */
        return;
    }
    ssr2::Arm *machineArm = machine->arm_();
    if (machineArm == nullptr || machineArm == NULL) {
#ifdef proc_verbose
        Serial.println(F("[proc::Solenoid] machine->arm_ is null"));
#endif /* proc_verbose */
        return;
    }
    ssr2::Hand *machineHand = machine->hand_();
    if (machineHand == nullptr || machineHand == NULL) {
#ifdef proc_verbose
        Serial.println(F("[proc::Solenoid] machine->machine_ is null"));
#endif /* proc_verbose */
        return;
    }
    if (_canFire(machineSolenoid, machineArm, machineHand)) {
        machineSolenoid->fire();
        _hand->status = ssr2::ProcessStatus::running;
        _requested = false;
#ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR("restart hand process, fire solenoid"));
#endif /* proc_verbose */
    } else {
        // 発射できないので、まずはハンドを開く
        _requested = true;
        _hand->status = ssr2::ProcessStatus::stopped;
        int16_t handAngle = machineHand->read();
        machineHand->write(handAngle + 1);
#ifdef proc_verbose
        ptr += snprintf_P(ptr, 200, PSTR("stop hand process, open hand"));
#endif /* proc_verbose */
    }
#ifdef proc_verbose
end:
    Serial.println(buffer);
#endif /* proc_verbose */
}
