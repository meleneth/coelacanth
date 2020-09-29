#ifndef CENTRAL_DISPATCH_MACHINE_HPP
#define CENTRAL_DISPATCH_MACHINE_HPP

#include "coelacanth_types.hpp"

namespace Coelacanth {

class CentralDispatchMachine {
  public:
    CentralDispatchMachine(UDPSocket *server_socket);
    ~CentralDispatchMachine();

    void possible_transition(CentralDispatchMachineState* new_state);
    
    virtual void parse_packet();
    
    CentralDispatchMachineState * state_;
    UDPSocket* socket;
};

}

#endif
