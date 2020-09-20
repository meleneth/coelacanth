#ifndef GAME_MACHINE_STATE_HPP
#define GAME_MACHINE_STATE_HPP

#include "coelacanth_types.hpp"

#include "game_machine.hpp"

namespace Coelacanth {

class GameMachineState {
  public:
    GameMachineState();
    virtual ~GameMachineState();

    virtual GameMachineState* tick(GameMachine& machine);
    virtual void onEnter();
    virtual void onExit();
};

}

#endif
