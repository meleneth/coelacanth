#ifndef TICKER_MACHINE_STATE_HPP
#define TICKER_MACHINE_STATE_HPP

#include "coelacanth_types.hpp"

#include "ticker_machine.hpp"

namespace Coelacanth {

class TickerMachine;

class TickerMachineState {
  public:
    TickerMachineState();
    virtual ~TickerMachineState();

    virtual TickerMachineState* tick(TickerMachine& machine);

    virtual void onEnter();
    virtual void onExit();
};

}

#endif
