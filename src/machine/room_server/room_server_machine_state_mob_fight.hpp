#ifndef ROOM_SERVER_MACHINE_STATE_MOB_FIGHT_HPP
#define ROOM_SERVER_MACHINE_STATE_MOB_FIGHT_HPP

#include "room_server_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class RoomServerMachineStateMobFight : public RoomServerMachineState {
  public:
    RoomServerMachineStateMobFight();
    virtual ~RoomServerMachineStateMobFight();
    virtual void onEnter(RoomServerMachine& machine);
    virtual void onExit(RoomServerMachine& machine);
    virtual RoomServerMachineState* recall(RoomServerMachine& machine);
};

}

#endif
