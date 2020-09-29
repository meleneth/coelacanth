#include "central_dispatch_machine_state_heartbeat.hpp"

#include"data_buffer.hpp"


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

CentralDispatchMachineState* CentralDispatchMachineStateHeartbeat::parse_packet(CentralDispatchMachine& machine, DataBuffer* buffer)
{
  if(buffer->starts_with("HEARTBEAT")) {
    LOG(INFO) << "[cDp] heartbeat state handled a heartbeat.  Go team!";
  }
  return nullptr;
}
