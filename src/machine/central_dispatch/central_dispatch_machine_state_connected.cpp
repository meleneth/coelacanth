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

CentralDispatchMachineState* CentralDispatchMachineStateConnected::parse_packet(CentralDispatchMachine& machine, DataBuffer* buffer, CentralDispatchMachineList& clients)
{
  LOG(INFO) << "[cD:Ms] <Connected> " << machine.listener->buffer.storage;
  return nullptr;
}
