#ifndef GAME_MACHINE_HPP
#define GAME_MACHINE_HPP

#include <memory>

#include "coelacanth_types.hpp"

namespace Coelacanth {

class GameMachine {
  public:
    GameMachine();
    ~GameMachine();

    void tick();

    void create_enemy();

    void add_player(Player *player);
    bool is_combat() const;
    bool is_enemy_died() const;

    Enemy *enemy;

    PlayerList players;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}

#endif
