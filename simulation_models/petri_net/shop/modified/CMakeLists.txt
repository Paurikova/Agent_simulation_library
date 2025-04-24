add_executable(Shop_petri_net
        src/main.cpp
        src/Manager1ReactiveReasoning.cpp
        src/Customer2ReactiveReasoning.cpp
        src/Shop3PetriNetReasoning.cpp
        src/Line4ReactiveReasoning.cpp
        src/Cash5PetriNetReasoning.cpp
        src/Graph6ReactiveReasoning.cpp
)

target_link_libraries(
        Shop_petri_net PRIVATE Simulation_interface_CASE_tool
)