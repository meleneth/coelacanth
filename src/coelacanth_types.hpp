#ifndef COELACANTH_HPP
#define COELACANTH_HPP

#include "easylogging++.h"

#include <map>
#include <string>
#include <vector>
#include <list>

namespace Coelacanth {
  class CentralDispatchMachine;
  class Client;
  class DataBuffer;
  class Enemy;
  class GameMachine;
  class Player;
  class Stats;
  class TickerMachine;
  class UDPSocket;
  class Weapon;
  class WorldServerMachine;
  class RoomServerMachine;
  typedef int PositionType;
  typedef std::list<CentralDispatchMachine *> CentralDispatchMachineList;
  typedef std::list<Client *> ClientList;
  typedef std::list<Player *> PlayerList;
  typedef std::list<RoomServerMachine *> RoomServerMachineList;
  typedef std::list<UDPSocket *> UDPSocketList;
  typedef std::list<WorldServerMachine *> WorldServerMachineList;
  typedef struct { PositionType x; PositionType y; } Position;
}

#endif
