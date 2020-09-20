#ifndef GAME_MACHINE_HPP
#define GAME_MACHINE_HPP

#include "coelacanth_types.hpp"

#include "game_machine_state.hpp"

namespace Coelacanth {

class GameMachine {
  public:
    GameMachine();
    ~GameMachine();

    Client *client_for_listener(UDPSocket &listener);
    void tick();

    void create_enemy();

    GameMachineState* state_;
    Enemy *enemy;

    ClientList clients;
};

}

#endif
