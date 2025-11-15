cmake_minimum_required(VERSION 4.0)
project(liquid_people)
set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  message("Debug mode")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-sanitize-recover=all -Wall -Werror -Wsign-compare")
else(CMAKE_BUILD_TYPE MATCHES "Release")
  message("Release mode")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_executable(game_of_life game_of_life/main.cpp game_of_life/game_of_life.cpp)
add_executable(lattice_gas cellular_automata/main.cpp cellular_automata/lattice_gas.cpp)
add_executable(mol_dynamics molecular_dynamics/main.cpp molecular_dynamics/mol_dynamics.cpp)
target_link_libraries(game_of_life
    sfml-system
    sfml-window
    sfml-graphics
)
target_link_libraries(lattice_gas
    sfml-system
    sfml-window
    sfml-graphics
)
target_link_libraries(mol_dynamics
    sfml-system
    sfml-window
    sfml-graphics
)