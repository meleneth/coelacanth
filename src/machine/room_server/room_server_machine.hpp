#ifndef ROOM_SERVER_MACHINE_HPP
#define ROOM_SERVER_MACHINE_HPP

#include <memory>

#include "coelacanth_types.hpp"
#include "udp_socket.hpp"

namespace Coelacanth {

class RoomServerMachine {
  public:
    RoomServerMachine(UDPSocket* server_sock, GameMachine *running_game);
    ~RoomServerMachine();

    virtual void parse_packet(DataBuffer& buffer, RoomServerMachineList& clients);

    void heartbeat(RoomServerMachineList& clients);

    virtual void recall();

    void send(std::string message);
    bool is_client_join() const;
    bool is_heartbeat() const;

    GameMachine *game;
    Player *player;

    UDPSocket socket;
    UDPSocket *listener;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}

#endif
