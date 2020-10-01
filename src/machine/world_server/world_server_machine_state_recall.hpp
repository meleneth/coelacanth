#ifndef WORLD_SERVER_MACHINE_STATE_RECALL_HPP
#define WORLD_SERVER_MACHINE_STATE_RECALL_HPP

#include "world_server_machine_state.hpp"

#include "coelacanth_types.hpp"

namespace Coelacanth {

class WorldServerMachineStateRecall : public WorldServerMachineState {
  public:
    WorldServerMachineStateRecall();
    virtual ~WorldServerMachineStateRecall();

    virtual void onEnter(WorldServerMachine& machine);
    virtual void onExit(WorldServerMachine& machine);

    virtual WorldServerMachineState* parse_packet(WorldServerMachine& machine, DataBuffer& buffer);
};

}

#endif
