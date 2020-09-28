#include "world_machine_state.hpp"

using namespace Coelacanth;

WorldMachineState::WorldMachineState()
{
}

WorldMachineState::~WorldMachineState()
{
}

void WorldMachineState::onEnter(WorldMachine& machine)
{
}

void WorldMachineState::onExit(WorldMachine& machine)
{
}

WorldMachineState* WorldMachineState::tick(WorldMachine& machine)
{
  return nullptr;
}
