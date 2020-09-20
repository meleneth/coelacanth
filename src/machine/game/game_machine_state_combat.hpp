#ifndef GAME_MACHINE_STATE_COMBAT_HPP
#define GAME_MACHINE_STATE_COMBAT_HPP

#include "coelacanth_types.hpp"

#include "game_machine.hpp"
#include "game_machine_state.hpp"

namespace Coelacanth {

class GameMachineStateCombat : public GameMachineState {
  public:
    GameMachineStateCombat();
    virtual ~GameMachineStateCombat();

    virtual GameMachineState* tick(GameMachine& machine);
    virtual void onEnter();
    virtual void onExit();
};

}

#endif
