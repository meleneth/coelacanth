#ifndef ROOM_SERVER_MACHINE_STATE_HEARTBEAT_HPP
#define ROOM_SERVER_MACHINE_STATE_HEARTBEAT_HPP

#include "room_server_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class RoomServerMachineStateHeartbeat : public RoomServerMachineState {
  public:
    RoomServerMachineStateHeartbeat();
    virtual ~RoomServerMachineStateHeartbeat();

    virtual void onEnter(RoomServerMachine& machine);
    virtual void onExit(RoomServerMachine& machine);

    virtual RoomServerMachineState* parse_packet(RoomServerMachine& machine, DataBuffer& buffer, RoomServerMachineList& clients) override;
    virtual RoomServerMachineState* recall(RoomServerMachine& machine);
};

}

#endif
