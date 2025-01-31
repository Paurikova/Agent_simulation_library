cmake_minimum_required(VERSION 3.22)

project(Agent_simulation_library)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt 8.0.0 REQUIRED)

# Include the library
add_subdirectory(library)

# Include the frontend project
#add_subdirectory(frontend)

# Include the frontend project
#add_subdirectory(frontend)

# Add your executable with agent1.cpp and agent2.cpp
add_executable(Agent_simulation_library main.cpp
       # frontend/CASE_tool/src/agentGenerator.cpp
        backend/src/agent1ReactiveReasoning.cpp
        backend/src/agent2ReactiveReasoning.cpp
        backend/src/simCoreReactiveReasoning.cpp
        backend/src/agent3ReactiveReasoning.cpp
        backend/src/agent1PetriNetReasoning.cpp
        Obchod/customer.cpp
        Obchod/manager.cpp
        Obchod/shop.cpp
        Obchod/cash_register.cpp
        Obchod/line_manager.cpp)
#backend/src/agentGenerator.cpp backend/src/agentTemplate.cpp
# Link with the library
target_link_libraries(Agent_simulation_library library)

target_link_libraries(Agent_simulation_library fmt)