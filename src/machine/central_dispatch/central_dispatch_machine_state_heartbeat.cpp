#include "central_dispatch_machine_state_heartbeat.hpp"

#include"data_buffer.hpp"

#include "central_dispatch_machine.hpp"

using namespace Coelacanth;

CentralDispatchMachineStateHeartbeat::CentralDispatchMachineStateHeartbeat()
{
  LOG(INFO) << "[cD:Ms] StateHeartbeat created! " << this;
}

CentralDispatchMachineStateHeartbeat::~CentralDispatchMachineStateHeartbeat()
{
  LOG(INFO) << "[cD:Ms] StateHeartbeat destroyed " << this;
}

void CentralDispatchMachineStateHeartbeat::onEnter(CentralDispatchMachine& machine)
{
}

void CentralDispatchMachineStateHeartbeat::onExit(CentralDispatchMachine& machine)
{
}

CentralDispatchMachineState* CentralDispatchMachineStateHeartbeat::parse_packet(CentralDispatchMachine& machine, DataBuffer& buffer, CentralDispatchMachineList& clients)
{
  LOG(INFO) << "[cD:Ms] <Heartbeat> " << buffer.storage;
  if(buffer.starts_with("HEARTBEAT")) {
    LOG(INFO) << "[cDp] Passing HEARTBEAT to all clients..";
    machine.heartbeat(clients);
  }
  return nullptr;
}

void CentralDispatchMachineStateHeartbeat::heartbeat(CentralDispatchMachine& machine, CentralDispatchMachineList& clients)
{
}
