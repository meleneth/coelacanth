#ifndef ROOM_SERVER_MACHINE_STATE_CLIENT_JOIN_HPP
#define ROOM_SERVER_MACHINE_STATE_CLIENT_JOIN_HPP

#include "room_server_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class RoomServerMachineStateClientJoin : public RoomServerMachineState {
  public:
    RoomServerMachineStateClientJoin();
    virtual ~RoomServerMachineStateClientJoin();

    virtual void onEnter(RoomServerMachine& machine);
    virtual void onExit(RoomServerMachine& machine);

    virtual RoomServerMachineState* recall(RoomServerMachine& machine) override;
    virtual RoomServerMachineState* parse_packet(RoomServerMachine& machine, DataBuffer& buffer, RoomServerMachineList& clients) override;

    virtual void heartbeat(RoomServerMachine& machine, RoomServerMachineList& clients) override;
};

}

#endif
