#include "world_machine.hpp"

using namespace Coelacanth;

WorldMachine::WorldMachine()
{
}

WorldMachine::~WorldMachine()
{
}

void WorldMachine::possible_transition(WorldMachineState* new_state)
{
  if(new_state) {
    state_->onExit(*this);
    delete state_;
    state_ = new_state;
    state_->onEnter(*this);
  }
}

void WorldMachine::tick()
{
  possible_transition(state_->tick(*this));
}
