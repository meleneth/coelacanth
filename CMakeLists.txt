cmake_minimum_required(VERSION 3.20)

project(coelacanth LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

FetchContent_Declare(
  sml
  GIT_REPOSITORY https://github.com/boost-ext/sml.git
  GIT_TAG v1.1.11
)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.8.1
)

FetchContent_Declare(
  eventpp
  GIT_REPOSITORY https://github.com/wqking/eventpp.git
  GIT_TAG v0.1.3
)

FetchContent_MakeAvailable(sml Catch2 eventpp)

add_library(coelacanth_lib STATIC
  src/engine/data_buffer.cpp
  src/engine/game_bot.cpp
  src/engine/udp_socket.cpp
  src/game/enemy.cpp
  src/game/player.cpp
  src/game/stats.cpp
  src/game/weapon.cpp
  src/machine/central_dispatch/central_dispatch_machine.cpp
  src/machine/game/game_machine.cpp
  src/machine/room_server/room_server_machine.cpp
  src/machine/ticker/ticker_machine.cpp
  src/machine/world/world_machine.cpp
  src/machine/world_server/world_server_machine.cpp
)

target_include_directories(coelacanth_lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game
    ${CMAKE_CURRENT_SOURCE_DIR}/src/external
    ${eventpp_SOURCE_DIR}/include
)

target_compile_options(coelacanth_lib PRIVATE -Wall -Wextra)
target_link_libraries(coelacanth_lib PUBLIC sml::sml)

find_package(Threads REQUIRED)
target_link_libraries(coelacanth_lib PUBLIC Threads::Threads)

function(add_coelacanth_executable target source)
  add_executable(${target} ${source} src/external/easylogging++.cc)
  target_link_libraries(${target} PRIVATE coelacanth_lib)
  set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endfunction()

add_coelacanth_executable(coelacanth src/coelacanth.cpp)
add_coelacanth_executable(central_dispatch src/central_dispatch.cpp)
add_coelacanth_executable(heartbeat src/heartbeat.cpp)
add_coelacanth_executable(worldserver src/worldserver.cpp)
add_coelacanth_executable(roomserver src/roomserver.cpp)

add_executable(testcoelacanth src/test_coelacanth.cpp src/external/easylogging++.cc)
target_link_libraries(testcoelacanth PRIVATE coelacanth_lib Catch2::Catch2WithMain)
set_target_properties(testcoelacanth PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(CTest)
include(Catch)
catch_discover_tests(testcoelacanth)
