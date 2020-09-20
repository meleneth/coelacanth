#ifndef GAME_MACHINE_HPP
#define GAME_MACHINE_HPP

namespace Coelcalanth {

class GameMachine {
  public:
    GameMachine();
    ~GameMachine();

    GameMachineState* state_;
    Enemy *enemy;
};

}

#endif
