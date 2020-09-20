#ifndef TICKER_MACHINE_HPP
#define TICKER_MACHINE_HPP

#include "coelacanth_types.hpp"

#include"ticker_machine_state.hpp"

namespace Coelacanth {

class TickerMachine {
  public:
    TickerMachine();
    ~TickerMachine();

    TickerMachineState* state_;
    void tick();
};

}

#endif
