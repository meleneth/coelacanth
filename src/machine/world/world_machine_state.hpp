#ifndef WORLD_MACHINE_STATE_HPP
#define WORLD_MACHINE_STATE_HPP

#include "coelacanth_types.hpp"

#include "world_machine.hpp"

namespace Coelacanth {

class WorldMachine;

class WorldMachineState {
  public:
    WorldMachineState();
    virtual ~WorldMachineState();
    virtual void onEnter(WorldMachine& machine);
    virtual void onExit(WorldMachine& machine);
    virtual WorldMachineState* tick(WorldMachine& machine);
};

}

#endif
