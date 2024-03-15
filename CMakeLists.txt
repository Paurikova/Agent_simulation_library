cmake_minimum_required(VERSION 3.27)

project(Agent_simulation_library)

set(CMAKE_CXX_STANDARD 17)

# Include the library
add_subdirectory(library)

# Include the frontend project
add_subdirectory(frontend)

# Include the frontend project
#add_subdirectory(frontend)

# Add your executable with agent1.cpp and agent2.cpp
add_executable(Agent_simulation_library main.cpp backend/agents/agent1.cpp backend/agents/agent2.cpp)

# Link with the library
target_link_libraries(Agent_simulation_library library)