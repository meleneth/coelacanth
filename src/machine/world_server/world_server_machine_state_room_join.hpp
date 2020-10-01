#ifndef WORLD_SERVER_MACHINE_STATE_ROOM_JOIN_HPP
#define WORLD_SERVER_MACHINE_STATE_ROOM_JOIN_HPP

#include "world_server_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class WorldServerMachineStateRoomJoin : public WorldServerMachineState {
  public:
    WorldServerMachineStateRoomJoin();
    virtual ~WorldServerMachineStateRoomJoin();

    virtual void onEnter(WorldServerMachine& machine);
    virtual void onExit(WorldServerMachine& machine);

    virtual WorldServerMachineState* parse_packet(WorldServerMachine& machine, DataBuffer& buffer);
};

}

#endif
