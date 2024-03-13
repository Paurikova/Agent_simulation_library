#cmake_minimum_required(VERSION 3.27)
cmake_minimum_required(VERSION 3.20)
project(Agent_simulation_library)

set(CMAKE_CXX_STANDARD 17)

add_executable(Agent_simulation_library ../backend/main.cpp
        include/agent.h
        src/agent.cpp
        include/simulationCore.h
        include/message.h
        src/schedule.cpp
        include/schedule.h
        src/simulationCore.cpp
        ../agents/agent1.cpp
        ../agents/agent1.h
        ../agents/agent2.cpp
        ../agents/agent2.h
)