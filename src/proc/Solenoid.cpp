#include "proc/Solenoid.hpp"

bool proc::Solenoid::_canFire(ssr2::Machine *machine) const noexcept {
    // ソレノイドが発射してから十分に時間が経っているかどうか
    // アーム、ハンドが弾道に干渉しているかどうか
    if (machine->solenoid.isFired()) return false;
    // TODO: アーム、ハンドが弾道に干渉しているかどうか
    int armAngle = machine->arm.read();
    if (armAngle != -1 && armAngle <= 110) return true;
    int handAngle = machine->hand.read();
    if (handAngle != -1 && handAngle >= 75) return true;
    return false;
}

void proc::Solenoid::begin(ssr2::Machine *machine) {
    status = ssr2::ProcessStatus::running;
}

void proc::Solenoid::update(ssr2::Machine *machine) {
    const ssr2::PS4Value &value = machine->currentPS4Value();
    if (value.circle && _canFire(machine)) {
        machine->solenoid.fire();
    } else {
        int16_t handAngle = machine->hand.read();
        machine->hand.write(handAngle + 1);
    }
}
