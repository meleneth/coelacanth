#include "central_dispatch_machine_state_connected.hpp"


using namespace Coelacanth;

CentralDispatchMachineStateConnected::CentralDispatchMachineStateConnected()
{
}

CentralDispatchMachineStateConnected::~CentralDispatchMachineStateConnected()
{
}

void CentralDispatchMachineStateConnected::onEnter(CentralDispatchMachine& machine)
{
}

void CentralDispatchMachineStateConnected::onExit(CentralDispatchMachine& machine)
{
}

CentralDispatchMachineState* CentralDispatchMachineStateConnected::parse_packet(CentralDispatchMachine& machine, DataBuffer& buffer, CentralDispatchMachineList& clients)
{
  if(buffer.starts_with("HEARTBEAT")) {
    machine.heartbeat(clients);
  }
  return nullptr;
}

void CentralDispatchMachineStateConnected::heartbeat(CentralDispatchMachine& machine, CentralDispatchMachineList& clients)
{
  LOG(INFO) << "[cDp] <Connected> Passing along HEARTBEAT to " << machine.socket.remoteaddr.sin_port;
  machine.reply_socket.send("HEARTBEAT");
}

