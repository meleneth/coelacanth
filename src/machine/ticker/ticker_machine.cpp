#include "ticker_machine.hpp"

#include "ticker_machine_state_tock.hpp"

using namespace Coelacanth;

TickerMachine::TickerMachine()
{
  state_ = new TickerMachineStateTock();
}

TickerMachine::~TickerMachine()
{
}

void TickerMachine::tick()
{
  auto new_state = state_->tick(*this);
  if(new_state) {
    state_->onExit();
    delete state_;
    new_state->onEnter();
    state_ = new_state;
  }
}
