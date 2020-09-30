noinst_LIBRARIES = src/libcoelacanth.a
bin_PROGRAMS = bin/coelacanth bin/central_dispatch bin/heartbeat bin/worldserver bin/roomserver

ACLOCAL_AMFLAGS = -I m4

src_libcoelacanth_a_SOURCES = \
  src/client.cpp \
  src/client.hpp \
  src/random_selector.hpp \
  src/machine/room_server/room_server_machine.cpp \
  src/machine/room_server/room_server_machine.hpp \
  src/machine/room_server/room_server_machine_state.cpp \
  src/machine/room_server/room_server_machine_state.hpp \
  src/machine/room_server/room_server_machine_state_client_join.cpp \
  src/machine/room_server/room_server_machine_state_client_join.hpp \
  src/machine/room_server/room_server_machine_state_client_ready.cpp \
  src/machine/room_server/room_server_machine_state_client_ready.hpp \
  src/machine/room_server/room_server_machine_state_heartbeat.cpp \
  src/machine/room_server/room_server_machine_state_heartbeat.hpp \
  src/machine/room_server/room_server_machine_state_mob_fight.cpp \
  src/machine/room_server/room_server_machine_state_mob_fight.hpp \
  src/machine/room_server/room_server_machine_state_start.cpp \
  src/machine/room_server/room_server_machine_state_start.hpp \
  src/external/easylogging++.hpp \
  src/external/cxxopts.hpp \
  src/coelacanth_types.hpp \
  src/engine/data_buffer.cpp \
  src/engine/data_buffer.hpp \
  src/engine/game_bot.cpp \
  src/engine/game_bot.hpp \
  src/engine/udp_socket.cpp \
  src/engine/udp_socket.hpp \
  src/game/enemy.cpp \
  src/game/enemy.hpp \
  src/game/player.cpp \
  src/game/player.hpp \
  src/game/stats.cpp \
  src/game/stats.hpp \
  src/game/weapon.cpp \
  src/game/weapon.hpp \
  src/machine/central_dispatch/central_dispatch_machine.cpp \
  src/machine/central_dispatch/central_dispatch_machine.hpp \
  src/machine/central_dispatch/central_dispatch_machine_state.cpp \
  src/machine/central_dispatch/central_dispatch_machine_state.hpp \
  src/machine/central_dispatch/central_dispatch_machine_state_connected.cpp \
  src/machine/central_dispatch/central_dispatch_machine_state_connected.hpp \
  src/machine/central_dispatch/central_dispatch_machine_state_dead.cpp \
  src/machine/central_dispatch/central_dispatch_machine_state_dead.hpp \
  src/machine/central_dispatch/central_dispatch_machine_state_heartbeat.cpp \
  src/machine/central_dispatch/central_dispatch_machine_state_heartbeat.hpp \
  src/machine/game/game_machine.cpp \
  src/machine/game/game_machine.hpp \
  src/machine/game/game_machine_state.cpp \
  src/machine/game/game_machine_state.hpp \
  src/machine/game/game_machine_state_combat.cpp \
  src/machine/game/game_machine_state_combat.hpp \
  src/machine/game/game_machine_state_enemy_died.cpp \
  src/machine/game/game_machine_state_enemy_died.hpp \
  src/machine/ticker/ticker_machine.cpp \
  src/machine/ticker/ticker_machine.hpp \
  src/machine/ticker/ticker_machine_state.cpp \
  src/machine/ticker/ticker_machine_state.hpp \
  src/machine/ticker/ticker_machine_state_tick.cpp \
  src/machine/ticker/ticker_machine_state_tick.hpp \
  src/machine/ticker/ticker_machine_state_tock.cpp \
  src/machine/ticker/ticker_machine_state_tock.hpp \
  src/machine/world/world_machine.cpp \
  src/machine/world/world_machine.hpp \
  src/machine/world/world_machine_state.cpp \
  src/machine/world/world_machine_state.hpp \
  src/machine/world/world_machine_state_construct.cpp \
  src/machine/world/world_machine_state_construct.hpp \
  src/machine/world/world_machine_state_end.cpp \
  src/machine/world/world_machine_state_end.hpp \
  src/machine/world/world_machine_state_populate.cpp \
  src/machine/world/world_machine_state_populate.hpp \
  src/machine/world/world_machine_state_simulate.cpp \
  src/machine/world/world_machine_state_simulate.hpp \
  src/machine/world_server/world_server_machine.cpp \
  src/machine/world_server/world_server_machine.hpp \
  src/machine/world_server/world_server_machine_state.cpp \
  src/machine/world_server/world_server_machine_state.hpp \
  src/machine/world_server/world_server_machine_state_login.cpp \
  src/machine/world_server/world_server_machine_state_login.hpp \
  src/machine/world_server/world_server_machine_state_recall.cpp \
  src/machine/world_server/world_server_machine_state_recall.hpp \
  src/machine/world_server/world_server_machine_state_room_join.cpp \
  src/machine/world_server/world_server_machine_state_room_join.hpp \
  src/machine/world_server/world_server_machine_state_welcome.cpp \
  src/machine/world_server/world_server_machine_state_welcome.hpp 

bin_coelacanth_SOURCES = src/coelacanth.cpp src/external/easylogging++.cc src/easylogging++.h
bin_central_dispatch_SOURCES = src/central_dispatch.cpp src/external/easylogging++.cc src/easylogging++.h
bin_heartbeat_SOURCES = src/heartbeat.cpp src/external/easylogging++.cc src/easylogging++.h
bin_worldserver_SOURCES = src/worldserver.cpp src/external/easylogging++.cc src/easylogging++.h
bin_roomserver_SOURCES = src/roomserver.cpp src/external/easylogging++.cc src/easylogging++.h

# Linux
AM_CXXFLAGS = -g -fno-inline -Wall -I/usr/local/include -D_GNU_SOURCE=1 -D_THREAD_SAFE -Isrc -Isrc/engine -Isrc/game -Isrc/external
bin_coelacanth_LDADD = -L/usr/lib -L/usr/local/lib -L/usr/local/lib -L/usr/lib/i386-linux-gnu -Lsrc src/libcoelacanth.a -lSDL2 -lSDL2_image -lSDL2_mixer
bin_central_dispatch_LDADD = -L/usr/lib -L/usr/local/lib -L/usr/local/lib -L/usr/lib/i386-linux-gnu -Lsrc src/libcoelacanth.a -lSDL2 -lSDL2_image -lSDL2_mixer
bin_heartbeat_LDADD = -L/usr/lib -L/usr/local/lib -L/usr/local/lib -L/usr/lib/i386-linux-gnu -Lsrc src/libcoelacanth.a -lSDL2 -lSDL2_image -lSDL2_mixer
bin_worldserver_LDADD = -L/usr/lib -L/usr/local/lib -L/usr/local/lib -L/usr/lib/i386-linux-gnu -Lsrc src/libcoelacanth.a -lSDL2 -lSDL2_image -lSDL2_mixer
bin_roomserver_LDADD = -L/usr/lib -L/usr/local/lib -L/usr/local/lib -L/usr/lib/i386-linux-gnu -Lsrc src/libcoelacanth.a -lSDL2 -lSDL2_image -lSDL2_mixer
