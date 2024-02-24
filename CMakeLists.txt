cmake_minimum_required(VERSION 3.27)
project(Agent_simulation_library)

set(CMAKE_CXX_STANDARD 17)

add_executable(Agent_simulation_library main.cpp
        agent.h
        goal.h
        agent.cpp
        goal.cpp
        action.h
        helloAction.h
        helloAction.cpp
)
