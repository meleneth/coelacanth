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
  class GameTickMachine;
  class GameTickState;
  class GameTickStateTick;
  class GameTickStateTock;
  class Player;
  class Enemy;
  class Stats;
  class Weapon;
  typedef std::list<GameClient> GameClientList;
  typedef std::list<UDPSocket *> UDPSocketList;
}

#endif
