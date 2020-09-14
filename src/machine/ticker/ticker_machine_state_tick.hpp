#ifndef TICKER_MACHINE_STATE_TICK_HPP
#define TICKER_MACHINE_STATE_TICK_HPP

#include "ticker_machine_state.hpp"

namespace Coelacanth {

class TickerMachineStateTick : public TickerMachineState {
  public:
    TickerMachineStateTick();
    virtual ~TickerMachineStateTick();

    virtual TickerMachineState* tick(TickerMachine& machine);

    virtual void onEnter();
};

}

#endif
