#ifndef CENTRAL_DISPATCH_MACHINE_STATE_CONNECTED_HPP
#define CENTRAL_DISPATCH_MACHINE_STATE_CONNECTED_HPP

#include "central_dispatch_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class CentralDispatchMachineStateConnected : public CentralDispatchMachineState {
  public:
    CentralDispatchMachineStateConnected();
    virtual ~CentralDispatchMachineStateConnected();

    virtual void onEnter(CentralDispatchMachine& machine) override;
    virtual void onExit(CentralDispatchMachine& machine) override;

    virtual CentralDispatchMachineState* parse_packet(CentralDispatchMachine& machine, DataBuffer& buffer, CentralDispatchMachineList& clients) override;
    virtual void heartbeat(CentralDispatchMachine& machine, CentralDispatchMachineList& clients) override;
};

}

#endif
