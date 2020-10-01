#ifndef ROOM_SERVER_MACHINE_HPP
#define ROOM_SERVER_MACHINE_HPP

#include "coelacanth_types.hpp"
#include "udp_socket.hpp"

namespace Coelacanth {

class RoomServerMachine {
  public:
    RoomServerMachine(UDPSocket* server_sock, GameMachine *running_game);
    ~RoomServerMachine();

    virtual void parse_packet(DataBuffer& buffer, RoomServerMachineList& clients);

    void possible_transition(RoomServerMachineState* new_state);
    void heartbeat(RoomServerMachineList& clients);

    virtual void recall();

    RoomServerMachineState * state_;
    
    GameMachine *game;
    Player *player;

    UDPSocket socket;
    UDPSocket *listener;
};

}

#endif
