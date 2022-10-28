#include "proc/NeoPixel.hpp"

void proc::NeoPixel::begin(ssr2::Machine *machine) {
    status = ssr2::ProcessStatus::running;
}

void proc::NeoPixel::update(ssr2::Machine *machine) {
    Adafruit_NeoPixel *machinePixels = machine->pixels();
    if (machinePixels == nullptr || machinePixels == NULL) {
        return;
    }
    uint16_t numLEDs = machinePixels->numPixels();
    const ssr2::PS4Value &value = machine->currentPS4Value();
    // L2: brightness
    uint8_t brightness = min(max(value.l2, 10), 100);
    // R2: color-transition speed
    // float hueSpeed = static_cast<float>(value.r2) / 255.0f * 5;
    // _firstHue += static_cast<uint16_t>(hueSpeed);
    uint16_t hueSpeed = min(value.r2, numLEDs);
    _firstHue += hueSpeed;
    // machinePixels->rainbow(_firstHue, 1, 255, brightness, true);
    for (uint16_t i = 0; i < numLEDs; i++) {
        uint16_t hue =
            _firstHue
            + static_cast<uint16_t>((static_cast<uint32_t>(i) << 16) / numLEDs);
        uint32_t color = Adafruit_NeoPixel::ColorHSV(hue, 255, brightness);
        machinePixels->setPixelColor(i, color);
    }
}
