#include "world_server_machine_state_welcome.hpp"


using namespace Coelacanth;

WorldServerMachineStateWelcome::WorldServerMachineStateWelcome()
{
}

WorldServerMachineStateWelcome::~WorldServerMachineStateWelcome()
{
}

void WorldServerMachineStateWelcome::onEnter(WorldServerMachine& machine)
{
}

void WorldServerMachineStateWelcome::onExit(WorldServerMachine& machine)
{
}

WorldServerMachineState* WorldServerMachineStateWelcome::parse_packet(WorldServerMachine& machine, DataBuffer& buffer)
{
  return nullptr;
}
