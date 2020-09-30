#include "room_server_machine_state.hpp"

using namespace Coelacanth;

RoomServerMachineState::RoomServerMachineState()
{
}

RoomServerMachineState::~RoomServerMachineState()
{
}

void RoomServerMachineState::onEnter(RoomServerMachine& machine)
{
}

void RoomServerMachineState::onExit(RoomServerMachine& machine)
{
}

void RoomServerMachineState::heartbeat(RoomServerMachine& machine, RoomServerMachineList& clients)
{
}

RoomServerMachineState* RoomServerMachineState::parse_packet(RoomServerMachine& machine, DataBuffer& buffer, CentralDispatchMachineList& clients)
{
  return nullptr;
}

RoomServerMachineState* RoomServerMachineState::recall(RoomServerMachine& machine)
{
  return nullptr;
}
