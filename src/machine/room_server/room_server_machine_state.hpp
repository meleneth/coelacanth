#ifndef ROOM_SERVER_MACHINE_STATE_HPP
#define ROOM_SERVER_MACHINE_STATE_HPP

#include "coelacanth_types.hpp"

namespace Coelacanth {

class RoomServerMachineState {
  public:
    RoomServerMachineState();
    virtual ~RoomServerMachineState();

    virtual void onEnter(RoomServerMachine& machine);
    virtual void onExit(RoomServerMachine& machine);

    virtual RoomServerMachineState* recall(RoomServerMachine& machine);
    virtual RoomServerMachineState* parse_packet(RoomServerMachine& machine, DataBuffer& buffer, RoomServerMachineList& clients);

    virtual void heartbeat(RoomServerMachine& machine, RoomServerMachineList& clients);
};

}

#endif
