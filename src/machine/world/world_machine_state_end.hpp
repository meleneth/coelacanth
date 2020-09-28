#ifndef WORLD_MACHINE_STATE_END_HPP
#define WORLD_MACHINE_STATE_END_HPP

#include "world_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class WorldMachineStateEnd : public WorldMachineState {
  public:
    WorldMachineStateEnd();
    virtual ~WorldMachineStateEnd();
    virtual void onEnter(WorldMachine& machine);
    virtual void onExit(WorldMachine& machine);
    virtual WorldMachineState* tick(WorldMachine& machine);
};

}

#endif
