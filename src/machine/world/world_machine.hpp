#ifndef WORLD_MACHINE_HPP
#define WORLD_MACHINE_HPP

#include "coelacanth_types.hpp"

#include "world_machine_state.hpp"

namespace Coelacanth {

class WorldMachineState;

class WorldMachine {
  public:
    WorldMachine();
    ~WorldMachine();

    void possible_transition(WorldMachineState* state);

    void tick();

    WorldMachineState * state_;
};

}

#endif
