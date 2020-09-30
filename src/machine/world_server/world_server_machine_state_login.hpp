#ifndef WORLD_SERVER_MACHINE_STATE_LOGIN_HPP
#define WORLD_SERVER_MACHINE_STATE_LOGIN_HPP

#include "world_server_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class WorldServerMachineStateLogin : public WorldServerMachineState {
  public:
    WorldServerMachineStateLogin();
    virtual ~WorldServerMachineStateLogin();
    virtual void onEnter(WorldServerMachine& machine);
    virtual void onExit(WorldServerMachine& machine);
    virtual WorldServerMachineState* parse_packet(WorldServerMachine& machine, DataBuffer& buffer);
};

}

#endif
