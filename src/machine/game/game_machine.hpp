#ifndef GAME_MACHINE_HPP
#define GAME_MACHINE_HPP

#include "coelacanth_types.hpp"

namespace Coelacanth {

class GameMachine {
  public:
    GameMachine();
    ~GameMachine();

    void possible_transition(GameMachineState *new_state);

    void tick();

    void create_enemy();

    void add_player(Player *player);

    GameMachineState* state_;
    Enemy *enemy;

    PlayerList players;
};

}

#endif
