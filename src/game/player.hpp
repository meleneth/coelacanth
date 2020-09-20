#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <coelacanth_types.hpp>
#include "stats.hpp"

namespace Coelacanth {

class Player {
  public:
    Player();
    ~Player();

    void hit(Enemy& enemy);

    std::string name;
    Stats stats;
};

}

#endif
