#ifndef WORLD_SERVER_MACHINE_HPP
#define WORLD_SERVER_MACHINE_HPP

#include "coelacanth_types.hpp"

namespace Coelacanth {

class WorldServerMachine {
  public:
    WorldServerMachine(UDPSocket* server_socket);
    ~WorldServerMachine();

    void possible_transition(WorldServerMachineState* new_state);

    virtual void parse_packet(DataBuffer& buffer);

    WorldServerMachineState * state_;
    UDPSocket* socket;

};

}

#endif
