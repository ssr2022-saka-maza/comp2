#include "ssr2/Process.hpp"

namespace proc {

class ForkLift : public ssr2::Process {
public:
    virtual void begin(ssr2::Machine * machine) override;
    virtual void update(ssr2::Machine * machine) override;
};  // class ForkLift

}  // namespace proc
