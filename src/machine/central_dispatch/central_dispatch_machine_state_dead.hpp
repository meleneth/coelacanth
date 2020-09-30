#ifndef CENTRAL_DISPATCH_MACHINE_STATE_DEAD_HPP
#define CENTRAL_DISPATCH_MACHINE_STATE_DEAD_HPP

#include "central_dispatch_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class CentralDispatchMachineStateDead : public CentralDispatchMachineState {
  public:
    CentralDispatchMachineStateDead();
    virtual ~CentralDispatchMachineStateDead();

    virtual void onEnter(CentralDispatchMachine& machine);
    virtual void onExit(CentralDispatchMachine& machine);

    virtual CentralDispatchMachineState* parse_packet(CentralDispatchMachine& machine, DataBuffer* buffer, CentralDispatchMachineList& clients);
};

}

#endif
