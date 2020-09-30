#include "central_dispatch_machine_state_heartbeat.hpp"

#include"data_buffer.hpp"

#include "central_dispatch_machine.hpp"

using namespace Coelacanth;

CentralDispatchMachineStateHeartbeat::CentralDispatchMachineStateHeartbeat()
{
}

CentralDispatchMachineStateHeartbeat::~CentralDispatchMachineStateHeartbeat()
{
}

void CentralDispatchMachineStateHeartbeat::onEnter(CentralDispatchMachine& machine)
{
}

void CentralDispatchMachineStateHeartbeat::onExit(CentralDispatchMachine& machine)
{
}

CentralDispatchMachineState* CentralDispatchMachineStateHeartbeat::parse_packet(CentralDispatchMachine& machine, DataBuffer* buffer, CentralDispatchMachineList& clients)
{
  if(buffer->starts_with("HEARTBEAT")) {
    LOG(INFO) << "[cDp] heartbeat state handled a heartbeat.  Go team!";
    LOG(INFO) << "[cDp] Passing HEARTBEAT to all clients..";
    for (auto client : clients) {
      LOG(INFO) << "[cDp] Passing HEARTBEAT to client";
      client->socket.send("HEARTBEAT beat_id");
    }
  }
  return nullptr;
}
