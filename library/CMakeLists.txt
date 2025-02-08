cmake_minimum_required(VERSION 3.22)

project(Agent_library)

set(CMAKE_CXX_STANDARD 17)

# Add source files
set(SOURCES
        src/simulationCore.cpp
        src/agent.cpp
        src/message.cpp
        src/schedule.cpp
        src/petriNetReasoning.cpp
        src/reactiveReasoning.cpp
        include/types.h
        src/agentReasoning.cpp
        include/state.h
)

# Create a static library
add_library(Agent_library STATIC ${SOURCES})

# Specify include directories
target_include_directories(Agent_library PUBLIC include)

# Link with the library
target_link_libraries(Agent_library PRIVATE units)