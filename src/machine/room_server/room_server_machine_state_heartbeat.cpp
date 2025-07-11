#include "room_server_machine_state_heartbeat.hpp"
#include "room_server_machine.hpp"


using namespace Coelacanth;

RoomServerMachineStateHeartbeat::RoomServerMachineStateHeartbeat()
{
}

RoomServerMachineStateHeartbeat::~RoomServerMachineStateHeartbeat()
{
}

void RoomServerMachineStateHeartbeat::onEnter(RoomServerMachine& machine)
{
}

void RoomServerMachineStateHeartbeat::onExit(RoomServerMachine& machine)
{
}

RoomServerMachineState* RoomServerMachineStateHeartbeat::parse_packet(RoomServerMachine& machine, DataBuffer& buffer, RoomServerMachineList& clients)
{
  LOG(INFO) << "[RS:SM] got HeartBEAT";
  for (auto client : clients) {
    client->send("TICK tick_id");
  }
  return nullptr;
}

RoomServerMachineState* RoomServerMachineStateHeartbeat::recall(RoomServerMachine& machine)
{
  return nullptr;
}
