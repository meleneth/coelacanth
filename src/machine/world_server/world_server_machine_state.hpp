#ifndef WORLD_SERVER_MACHINE_STATE_HPP
#define WORLD_SERVER_MACHINE_STATE_HPP

#include "coelacanth_types.hpp"

namespace Coelacanth {

class WorldServerMachineState {
  public:
    WorldServerMachineState();
    virtual ~WorldServerMachineState();

    virtual void onEnter(WorldServerMachine& machine);
    virtual void onExit(WorldServerMachine& machine);

    virtual WorldServerMachineState* parse_packet(WorldServerMachine& machine, DataBuffer& buffer);
};

}

#endif
