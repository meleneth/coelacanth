#ifndef WORLD_SERVER_MACHINE_STATE_WELCOME_HPP
#define WORLD_SERVER_MACHINE_STATE_WELCOME_HPP

#include "world_server_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class WorldServerMachineStateWelcome : public WorldServerMachineState {
  public:
    WorldServerMachineStateWelcome();
    virtual ~WorldServerMachineStateWelcome();
    virtual void onEnter(WorldServerMachine& machine);
    virtual void onExit(WorldServerMachine& machine);
    virtual WorldServerMachineState* parse_packet(WorldServerMachine& machine);
};

}

#endif
