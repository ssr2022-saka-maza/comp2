#pragma once

#include "ssr2/Process.hpp"

namespace proc {

class Hand : public ssr2::Process {
public:
    virtual void begin(ssr2::Machine *machine) override;
    virtual void update(ssr2::Machine *machine) override;
}; // class Hand

} // namespace proc
