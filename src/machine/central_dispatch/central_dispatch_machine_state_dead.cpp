#include "central_dispatch_machine_state_dead.hpp"


using namespace Coelacanth;

CentralDispatchMachineStateDead::CentralDispatchMachineStateDead()
{
}

CentralDispatchMachineStateDead::~CentralDispatchMachineStateDead()
{
}

void CentralDispatchMachineStateDead::onEnter(CentralDispatchMachine& machine)
{
}

void CentralDispatchMachineStateDead::onExit(CentralDispatchMachine& machine)
{
}

CentralDispatchMachineState* CentralDispatchMachineStateDead::parse_packet(CentralDispatchMachine& machine, DataBuffer& buffer, CentralDispatchMachineList& clients)
{
  return nullptr;
}
