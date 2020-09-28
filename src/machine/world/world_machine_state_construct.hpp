#ifndef WORLD_MACHINE_STATE_CONSTRUCT_HPP
#define WORLD_MACHINE_STATE_CONSTRUCT_HPP

#include "world_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class WorldMachine;

class WorldMachineStateConstruct : public WorldMachineState {
  public:
    WorldMachineStateConstruct();
    virtual ~WorldMachineStateConstruct();
    virtual void onEnter(WorldMachine& machine);
    virtual void onExit(WorldMachine& machine);
    virtual WorldMachineState* tick(WorldMachine& machine);
};

}

#endif
