#ifndef COELACANTH_HPP
#define COELACANTH_HPP

#include <map>
#include <string>
#include <vector>
#include <list>

namespace Coelacanth {
  class Client;
  class DataBuffer;
  class Enemy;
  class GameMachine;
  class GameMachineState;
  class GameMachineStateCombat;
  class GameMachineStateEnemyDied;
  class Player;
  class Stats;
  class TickerMachine;
  class TickerMachine;
  class TickerMachineState;
  class TickerMachineStateTick;
  class TickerMachineStateTock;
  class UDPSocket;
  class Weapon;
  typedef std::list<Client *> ClientList;
  typedef std::list<UDPSocket *> UDPSocketList;
}

#endif
