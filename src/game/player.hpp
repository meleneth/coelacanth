#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "coelacanth_types.hpp"
#include "stats.hpp"

namespace Coelacanth {

class Player {
  public:
    Player();
    ~Player();

    std::string name;
    Stats stats;
};

}

#endif
