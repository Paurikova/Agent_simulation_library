cmake_minimum_required(VERSION 3.22)

project(Agent_simulation_library)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt 8.0.0 REQUIRED)

# Include the library
add_subdirectory(library)

# Include the frontend project
#add_subdirectory(frontend)

# Include the frontend project
#TODO
#add_subdirectory(frontend)

# Add your executable with agent1.cpp and agent2.cpp
add_executable(Agent_simulation_library main.cpp
       # frontend/CASE_tool/src/agentGenerator.cpp
        Obchod_better/manager.cpp
        Obchod_better/customer.h
        Obchod_better/customer.cpp
        Obchod_better/shop.cpp
        Obchod_better/line.cpp
        Obchod_better/cash.cpp
        Obchod_better/state.h
#        flocking_model_petri_net/bird.cpp
        units/scr/logger.cpp
        units/scr/fileManager.cpp)
#        flocking_model/bird.cpp
#        flocking_model/manager.cpp)
#backend/src/agentGenerator.cpp backend/src/agentTemplate.cpp
# Link with the library
target_link_libraries(Agent_simulation_library library)

target_link_libraries(Agent_simulation_library fmt)

# Find SFML
find_package(SFML 2.5 REQUIRED graphics window system)

# Link SFML libraries to the project
target_link_libraries(Agent_simulation_library sfml-graphics sfml-window sfml-system)