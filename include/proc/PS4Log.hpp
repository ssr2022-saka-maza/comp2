#pragma once

#include "ssr2/App.hpp"

namespace proc {

class PS4Log : public ssr2::Process {
private:
    virtual void begin(ssr2::Machine * machine) override;
    virtual void update(ssr2::Machine * machine) override;
};  // class PS4Log

}  // namespace proc
