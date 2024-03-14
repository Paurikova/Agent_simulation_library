#cmake_minimum_required(VERSION 3.27)
cmake_minimum_required(VERSION 3.20)
project(Agent_simulation_library)

set(CMAKE_CXX_STANDARD 17)

add_executable(Agent_simulation_library ../main.cpp
        ../backend/agents/agent1.cpp
        ../backend/agents/agent2.cpp
        src/simulationCore.cpp
        src/agent.cpp
        src/message.cpp
        src/schedule.cpp
)