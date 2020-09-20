#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "coelacanth_types.hpp"

#include <udp_socket.hpp>
#include "player.hpp"

namespace Coelacanth {

class Client {
  public:
    Client(UDPSocket& server_socket);
    ~Client();

    UDPSocket socket;
    Player player;
};

}

#endif
