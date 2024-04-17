cmake_minimum_required(VERSION 3.22)

project(library_test)

set(CMAKE_CXX_STANDARD 17)

# Add your executable with agent1.cpp and agent2.cpp
add_executable(library_test agents/src/agent1.cpp agents/src/agent2.cpp)

# Link with the library
target_link_libraries(Agent_simulation_library library)