#include "world_machine_state_end.hpp"


using namespace Coelacanth;

WorldMachineStateEnd::WorldMachineStateEnd()
{
}

WorldMachineStateEnd::~WorldMachineStateEnd()
{
}

void WorldMachineStateEnd::onEnter(WorldMachine& machine)
{
}

void WorldMachineStateEnd::onExit(WorldMachine& machine)
{
}

WorldMachineState* WorldMachineStateEnd::tick(WorldMachine& machine)
{
  return nullptr;
}
