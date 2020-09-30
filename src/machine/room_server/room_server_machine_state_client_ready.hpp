#ifndef ROOM_SERVER_MACHINE_STATE_CLIENT_READY_HPP
#define ROOM_SERVER_MACHINE_STATE_CLIENT_READY_HPP

#include "room_server_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class RoomServerMachineStateClientReady : public RoomServerMachineState {
  public:
    RoomServerMachineStateClientReady();
    virtual ~RoomServerMachineStateClientReady();
    virtual void onEnter(RoomServerMachine& machine);
    virtual void onExit(RoomServerMachine& machine);
    virtual RoomServerMachineState* recall(RoomServerMachine& machine);
};

}

#endif
