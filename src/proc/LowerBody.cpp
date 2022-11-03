#include "proc/LowerBody.hpp"

const float proc::LowerBody::_sqrt2 = sqrt(2.0);

float proc::LowerBody::_mapPower(uint8_t value) noexcept {
    int16_t trans = value - 128;
    return abs(trans) <= 8 ? 0 : float(trans) * _sqrt2;
}

void proc::LowerBody::begin(ssr2::Machine * machine) {
    status = ssr2::ProcessStatus::running;
}

void proc::LowerBody::update(ssr2::Machine * machine) {
    ssr2::LowerBody * lowerBody = machine->lowerBody();
    if (lowerBody == nullptr || lowerBody == NULL) {
#ifdef proc_verbose
        Serial.print("[proc::LowerBody] machine->lowerBody() is null");
#endif /* proc_verbose */
        return;
    }
    const ssr2::PS4Value & value = machine->currentPS4Value();
    float x = _mapPower(value.lstick.y);
    float y = _mapPower(value.lstick.x);
    float r = _mapPower(value.rstick.x);
#ifdef proc_verbose
    char buffer[256] = "";
    char * ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("[proc::LowerBody] twist "));
    dtostrf(x, 6, 2, ptr);
    ptr += 6;
    ptr[0] = ',';
    ptr[1] = ' ';
    ptr += 2;
    dtostrf(y, 6, 2, ptr);
    ptr += 6;
    ptr[0] = ',';
    ptr[1] = ' ';
    ptr += 2;
    dtostrf(r, 6, 2, ptr);
    ptr += 6;
    Serial.println(buffer);
#endif /* proc_verbose */
    lowerBody->twist(x, y, r);
}
