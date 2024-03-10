cmake_minimum_required(VERSION 3.27)
project(Agent_simulation_library)

set(CMAKE_CXX_STANDARD 17)

add_executable(Agent_simulation_library main.cpp
        agent.h
        agent.cpp
        managerAgent.h
        message.h
        schedule.cpp
        schedule.h
        managerAgent.cpp
        agents/agent1.cpp
        agents/agent1.h
        agents/agent2.cpp
        agents/agent2.h
)
