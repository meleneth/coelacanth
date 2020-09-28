#ifndef WORLD_MACHINE_STATE_POPULATE_HPP
#define WORLD_MACHINE_STATE_POPULATE_HPP

#include "world_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class WorldMachineStatePopulate : public WorldMachineState {
  public:
    WorldMachineStatePopulate();
    virtual ~WorldMachineStatePopulate();
    virtual void onEnter(WorldMachine& machine);
    virtual void onExit(WorldMachine& machine);
    virtual WorldMachineState* tick(WorldMachine& machine);
};

}

#endif
