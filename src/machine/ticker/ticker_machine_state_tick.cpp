#include "ticker_machine_state_tick.hpp"
#include "ticker_machine_state_tock.hpp"

#include "easylogging++.h"

using namespace Coelacanth;

TickerMachineStateTick::TickerMachineStateTick()
{
}

TickerMachineStateTick::~TickerMachineStateTick()
{
}

TickerMachineState *TickerMachineStateTick::tick(TickerMachine& machine)
{
  return new TickerMachineStateTock();
}

void TickerMachineStateTick::onEnter()
{
  LOG(INFO) << "onEnter(Tick)";
}
