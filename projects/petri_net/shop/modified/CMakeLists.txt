add_executable(Shop_petri_net_CASE_tool
        src/main_shop_petri_net.cpp
        src/Manager1ReactiveReasoning.cpp
        src/Customer2ReactiveReasoning.cpp
        src/Shop3PetriNetReasoning.cpp
        src/Line5PetriNetReasoning.cpp
        src/Cash6PetriNetReasoning.cpp
        src/Graph4ReactiveReasoning.cpp
)

target_link_libraries(
        Shop_petri_net_CASE_tool PRIVATE Simulation_interface_CASE_tool
)