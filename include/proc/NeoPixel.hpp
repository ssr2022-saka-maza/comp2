#pragma once

#include <Arduino.h>

#ifdef __AVR__
#include <avr/power.h>
#endif /* __AVR__ */

#include <Adafruit_NeoPixel.h>

#include <ssr2/Machine.hpp>
#include <ssr2/Process.hpp>
#include <ssr2/ProcessStatus.hpp>

namespace proc {

class NeoPixel : public ssr2::Process {
private:
    uint16_t _firstHue = 0;

public:
    virtual void begin(ssr2::Machine * machine) override;
    virtual void update(ssr2::Machine * machine) override;
};  // class NeoPixel

}  // namespace proc
