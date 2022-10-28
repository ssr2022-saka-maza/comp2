#include "proc/NeoPixel.hpp"

void proc::NeoPixel::begin(ssr2::Machine *machine) {
    status = ssr2::ProcessStatus::running;
}

void proc::NeoPixel::update(ssr2::Machine *machine) {
    Adafruit_NeoPixel *machinePixels = machine->pixels();
    if (machinePixels == nullptr || machinePixels == NULL) {
        return;
    }
    const ssr2::PS4Value &value = machine->currentPS4Value();
    // L2: brightness
    uint8_t brightness = max(value.l2, 10);
    // R2: color-transition speed
    float hueSpeed = static_cast<float>(value.r2) / 255.0f * 5;
    _firstHue += static_cast<uint16_t>(hueSpeed);
    machinePixels->rainbow(_firstHue, 1, 255, brightness, true);
}
