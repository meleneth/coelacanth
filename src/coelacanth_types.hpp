#ifndef COELACANTH_HPP
#define COELACANTH_HPP

#include <map>
#include <string>
#include <vector>
#include <list>

namespace Coelacanth {
  class GameClient;
  class GameServer;
  class UDPSocket;
  class DataBuffer;
  class GameMachineState;
  class GameMachineStateCombat;
  class GameMachineStateEnemyDied;
  class GameMachine;
  class TickerMachine;
  class TickerMachineStateTick;
  class TickerMachineStateTock;
  class TickerMachineState;
  class TickerMachine;
  class Player;
  class Enemy;
  class Stats;
  class Weapon;
  typedef std::list<GameClient> GameClientList;
  typedef std::list<UDPSocket *> UDPSocketList;
}

#endif
