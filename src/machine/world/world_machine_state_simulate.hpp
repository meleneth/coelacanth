#ifndef WORLD_MACHINE_STATE_SIMULATE_HPP
#define WORLD_MACHINE_STATE_SIMULATE_HPP

#include "world_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class WorldMachineStateSimulate : public WorldMachineState {
  public:
    WorldMachineStateSimulate();
    virtual ~WorldMachineStateSimulate();
    virtual void onEnter(WorldMachine& machine);
    virtual void onExit(WorldMachine& machine);
    virtual WorldMachineState* tick(WorldMachine& machine);
};

}

#endif
