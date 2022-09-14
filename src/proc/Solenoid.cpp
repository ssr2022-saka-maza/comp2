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

void proc::Solenoid::begin(ssr2::Machine *machine) {
    status = ssr2::ProcessStatus::running;
}

void proc::Solenoid::update(ssr2::Machine *machine) {
    const ssr2::PS4Value &value = machine->currentPS4Value();
    if (value.circle && _canFire(machine)) {
        machine->solenoid.fire();
    } else {
        // 発射できないので、まずはハンドを開く
        int16_t handAngle = machine->hand.read();
        machine->hand.write(handAngle + 3);
    }
}
