#include "central_dispatch_machine_state.hpp"
#include "central_dispatch_machine_state_heartbeat.hpp"
#include"data_buffer.hpp"

using namespace Coelacanth;

CentralDispatchMachineState::CentralDispatchMachineState()
{
}

CentralDispatchMachineState::~CentralDispatchMachineState()
{
}

void CentralDispatchMachineState::onEnter(CentralDispatchMachine& machine)
{
}

void CentralDispatchMachineState::onExit(CentralDispatchMachine& machine)
{
}

CentralDispatchMachineState* CentralDispatchMachineState::parse_packet(CentralDispatchMachine& machine, DataBuffer* buffer)
{
  LOG(INFO) << "[cD:Ms] " << buffer;
  if(buffer->starts_with("HEARTBEAT")) {
    return new CentralDispatchMachineStateHeartbeat();
  }
  return nullptr;
}
