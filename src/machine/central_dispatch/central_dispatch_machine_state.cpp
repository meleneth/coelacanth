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
  if(buffer.starts_with("HEARTBEAT")) {
    return new CentralDispatchMachineStateHeartbeat();
  }
  if (machine.listener->buffer.starts_with("SERVREADY ")) {
    LOG(INFO) << " Hello server!  I'll call you " << machine.listener->remoteaddr.sin_port;
    return new CentralDispatchMachineStateConnected();
  } else {
    LOG(INFO) << "[cD:Ms] watch out it's the cops says: get out of here with your " << machine.listener->buffer.storage;
  }
  return nullptr;
}

void CentralDispatchMachineState::heartbeat(CentralDispatchMachine& machine, CentralDispatchMachineList& clients)
{
  LOG(INFO) << "[cDp] <Connected> Passing along HEARTBEAT to " << machine.socket.remoteaddr.sin_port;
  machine.socket.send("HEARTBEAT");
}
