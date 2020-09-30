#include "central_dispatch_machine_state.hpp"
#include "central_dispatch_machine_state_heartbeat.hpp"
#include "central_dispatch_machine_state_connected.hpp"
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

CentralDispatchMachineState* CentralDispatchMachineState::parse_packet(CentralDispatchMachine& machine, DataBuffer& buffer, CentralDispatchMachineList& clients)
{
  LOG(INFO) << "[cD:Ms] " << buffer.storage;
  if(buffer.starts_with("HEARTBEAT")) {
    LOG(INFO) << " So we switch state here so wtf?";
    return new CentralDispatchMachineStateHeartbeat();
  }
  if (machine.listener->buffer.starts_with("SERVREADY ")) {
    return new CentralDispatchMachineStateConnected();
  } else {
    LOG(INFO) << "[cD:Ms] watch out it's the cops says: get out of here with your " << machine.listener->buffer.storage;
  }
  return nullptr;
}

void CentralDispatchMachineState::heartbeat(CentralDispatchMachine& machine)
{
  LOG(INFO) << "[cD:Ms] echo heartbeat";
  machine.socket.send("HEARTBEAT");
}
