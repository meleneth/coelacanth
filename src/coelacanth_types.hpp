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
  typedef std::list<GameClient> GameClientList;
  typedef std::list<UDPSocket *> UDPSocketList;
}

#endif
