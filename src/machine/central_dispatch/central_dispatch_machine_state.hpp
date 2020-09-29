#ifndef CENTRAL_DISPATCH_MACHINE_STATE_HPP
#define CENTRAL_DISPATCH_MACHINE_STATE_HPP

#include "coelacanth_types.hpp"

namespace Coelacanth {

class CentralDispatchMachineState {
  public:
    CentralDispatchMachineState();
    virtual ~CentralDispatchMachineState();
    virtual void onEnter(CentralDispatchMachine& machine);
    virtual void onExit(CentralDispatchMachine& machine);
    virtual CentralDispatchMachineState* parse_packet(CentralDispatchMachine& machine, DataBuffer* buffer);
};

}

#endif
