#ifndef TICKER_MACHINE_STATE_TOCK_HPP
#define TICKER_MACHINE_STATE_TOCK_HPP

#include "ticker_machine_state.hpp"

namespace Coelacanth {

class TickerMachineStateTock : public TickerMachineState {
  public:
    TickerMachineStateTock();
    virtual ~TickerMachineStateTock();
    virtual TickerMachineState* tick(TickerMachine& machine);

    virtual void onEnter();
};

}

#endif
