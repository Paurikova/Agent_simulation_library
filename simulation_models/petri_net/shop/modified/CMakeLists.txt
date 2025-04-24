add_executable(Shop_petri_net
        src/main.cpp
        src/Manager1ReactiveReasoning.cpp
        src/Customer2ReactiveReasoning.cpp
        src/Shop4PetriNetReasoning.cpp
        src/Line5ReactiveReasoning.cpp
        src/Cash6PetriNetReasoning.cpp
        src/Graph3ReactiveReasoning.cpp
)

target_link_libraries(
        Shop_petri_net PRIVATE Simulation_interface_CASE_tool
)