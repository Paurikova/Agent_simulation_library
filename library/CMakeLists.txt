cmake_minimum_required(VERSION 3.22)

project(Agent_library)

set(CMAKE_CXX_STANDARD 17)

# Add all source files for the library
set(LIBRARY_SOURCES
        src/simulationCore.cpp
        src/agent.cpp
        src/message.cpp
        src/schedule.cpp
        src/petriNetReasoning.cpp
        src/reactiveReasoning.cpp
        include/types.h
        src/agentReasoning.cpp
        src/uniqueDeque.cpp
        include/state.h
)

# Create the library
add_library(library ${LIBRARY_SOURCES})

# Include directories if needed
target_include_directories(library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})