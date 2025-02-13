add_library(Agent_library STATIC
        src/simulationCore.cpp
        src/agent.cpp
        src/message.cpp
        src/schedule.cpp
        src/petriNetReasoning.cpp
        src/reactiveReasoning.cpp
        src/agentReasoning.cpp
)

target_include_directories(Agent_library PUBLIC include)

target_link_libraries(Agent_library PRIVATE units)