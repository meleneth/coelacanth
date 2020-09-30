#include "world_server_machine_state.hpp"

using namespace Coelacanth;

WorldServerMachineState::WorldServerMachineState()
{
}

WorldServerMachineState::~WorldServerMachineState()
{
}

void WorldServerMachineState::onEnter(WorldServerMachine& machine)
{
}

void WorldServerMachineState::onExit(WorldServerMachine& machine)
{
}

WorldServerMachineState* WorldServerMachineState::parse_packet(WorldServerMachine& machine, DataBuffer& buffer)
{
  return nullptr;
}
