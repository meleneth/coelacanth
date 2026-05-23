#ifndef WORLD_SERVER_MACHINE_HPP
#define WORLD_SERVER_MACHINE_HPP

#include <memory>

#include "coelacanth_types.hpp"
#include "udp_socket.hpp"

namespace Coelacanth {

class WorldServerMachine {
  public:
    WorldServerMachine(UDPSocket* server_socket);
    ~WorldServerMachine();

    virtual void parse_packet(DataBuffer& buffer);
    bool is_waiting() const;

    UDPSocket* socket;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}

#endif
