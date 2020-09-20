#ifndef GAME_MACHINE_HPP
#define GAME_MACHINE_HPP

#include "coelacanth_types.hpp"

#include "game_machine_state.hpp"

namespace Coelacanth {

class GameMachine {
  public:
    GameMachine();
    ~GameMachine();

    GameMachineState* state_;
    Enemy *enemy;
};

}

#endif
