noinst_LIBRARIES = src/libcoelacanth.a
bin_PROGRAMS = bin/coelacanth

ACLOCAL_AMFLAGS = -I m4

src_libcoelacanth_a_SOURCES = \
	src/coelacanth_types.hpp \
  src/engine/game_server.hpp \
  src/engine/game_server.cpp \
  src/engine/game_bot.hpp \
  src/engine/game_bot.cpp \
  src/engine/game_client.hpp \
  src/engine/game_client.cpp \
	src/engine/udp_socket.cpp \
	src/engine/udp_socket.hpp \
  src/engine/data_buffer.cpp \
  src/engine/data_buffer.hpp

bin_coelacanth_SOURCES = src/coelacanth.cpp src/easylogging++.cc src/easylogging++.h

# Linux
AM_CXXFLAGS = -g -fno-inline @LUA_INCLUDE@ -Wall -I/usr/include/lua5.1 -I/usr/local/include -I/www/include -D_GNU_SOURCE=1 -D_THREAD_SAFE -Isrc -Isrc/engine -I/usr/include/freetype2 -I external
bin_coelacanth_LDADD = -L/usr/lib -L/usr/local/lib -L/usr/local/lib -L/usr/lib/i386-linux-gnu -Lsrc src/libcoelacanth.a -llua5.1 -lSDL2 -lSDL2_image -lSDL2_mixer -lftgl -lGLEW
