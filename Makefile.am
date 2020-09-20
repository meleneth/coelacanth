noinst_LIBRARIES = src/libcoelacanth.a
bin_PROGRAMS = bin/coelacanth

ACLOCAL_AMFLAGS = -I m4

src_libcoelacanth_a_SOURCES = \
  src/coelacanth_types.hpp \
  src/engine/data_buffer.cpp \
  src/engine/data_buffer.hpp \
  src/engine/game_bot.cpp \
  src/engine/game_bot.hpp \
  src/engine/game_client.cpp \
  src/engine/game_client.hpp \
  src/engine/game_server.cpp \
  src/engine/game_server.hpp \
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
  src/machine/ticker/ticker_machine_state_tock.hpp

bin_coelacanth_SOURCES = src/coelacanth.cpp src/easylogging++.cc src/easylogging++.h

# Linux
AM_CXXFLAGS = -g -fno-inline -Wall -I/usr/local/include -D_GNU_SOURCE=1 -D_THREAD_SAFE -Isrc -Isrc/engine -I external
bin_coelacanth_LDADD = -L/usr/lib -L/usr/local/lib -L/usr/local/lib -L/usr/lib/i386-linux-gnu -Lsrc src/libcoelacanth.a -lSDL2 -lSDL2_image -lSDL2_mixer
