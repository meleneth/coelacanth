#ifndef ROOM_SERVER_MACHINE_STATE_START_HPP
#define ROOM_SERVER_MACHINE_STATE_START_HPP

#include "room_server_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class RoomServerMachineStateStart : public RoomServerMachineState {
  public:
    RoomServerMachineStateStart();
    virtual ~RoomServerMachineStateStart();
    virtual void onEnter(RoomServerMachine& machine);
    virtual void onExit(RoomServerMachine& machine);
    virtual RoomServerMachineState* recall(RoomServerMachine& machine);
};

}

#endif
