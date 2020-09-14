#include "easylogging++.h"

#include "ticker_machine_state_tock.hpp"
#include "ticker_machine_state_tick.hpp"

using namespace Coelacanth;

TickerMachineStateTock::TickerMachineStateTock()
{
}

TickerMachineStateTock::~TickerMachineStateTock()
{
}

TickerMachineState *TickerMachineStateTock::tick(TickerMachine& machine)
{
  return new TickerMachineStateTick();
}

void TickerMachineStateTock::onEnter()
{
  LOG(INFO) << "onEnter(Tock)";
}
