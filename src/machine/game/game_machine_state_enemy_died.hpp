#ifndef GAME_MACHINE_STATE_ENEMY_DIED_HPP
#define GAME_MACHINE_STATE_ENEMY_DIED_HPP

#include "coelacanth_types.hpp"

#include "game_machine.hpp"
#include "game_machine_state.hpp"

namespace Coelacanth {

class GameMachineStateEnemyDied : public GameMachineState {
  public:
    GameMachineStateEnemyDied();
    virtual ~GameMachineStateEnemyDied();

    virtual GameMachineState* tick(GameMachine& machine);
    virtual void onEnter();
    virtual void onExit();

};

}

#endif
