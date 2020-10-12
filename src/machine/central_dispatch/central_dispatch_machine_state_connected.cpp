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
    LOG(INFO) << "[cDp] got heartbeat, sending to attached servers";
    machine.heartbeat(clients);
  }
  return nullptr;
}

void CentralDispatchMachineStateConnected::heartbeat(CentralDispatchMachine& machine, CentralDispatchMachineList& clients)
{
  LOG(INFO) << "[cDp] <Connected> " << &machine << " Passing along HEARTBEAT to " << machine.reply_socket.myaddr.sin_port;
  machine.reply_socket.send("HEARTBEAT");
}

