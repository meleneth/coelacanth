#ifndef COELACANTH_HPP
#define COELACANTH_HPP

#include <map>
#include <string>
#include <vector>
#include <list>

namespace Coelacanth {
  class GameClient;
  class GameServer;
  class UDPListener;
  class UDPSender;
  typedef std::list<GameClient> GameClientList;
}

#endif
