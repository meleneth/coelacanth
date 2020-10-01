#include "room_server_machine_state_client_join.hpp"


using namespace Coelacanth;

RoomServerMachineStateClientJoin::RoomServerMachineStateClientJoin()
{
}

RoomServerMachineStateClientJoin::~RoomServerMachineStateClientJoin()
{
}

void RoomServerMachineStateClientJoin::onEnter(RoomServerMachine& machine)
{
}

void RoomServerMachineStateClientJoin::onExit(RoomServerMachine& machine)
{
}

RoomServerMachineState* RoomServerMachineStateClientJoin::recall(RoomServerMachine& machine)
{
  return nullptr;
}

void RoomServerMachineStateClientJoin::heartbeat(RoomServerMachine& machine, RoomServerMachineList& clients)
{
}
