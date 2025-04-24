add_executable(Shop_reactive
        src/main.cpp
        src/Manager1ReactiveReasoning.cpp
        src/Customer4ReactiveReasoning.cpp
        src/Shop3ReactiveReasoning.cpp
        src/Line5ReactiveReasoning.cpp
        src/Cash6ReactiveReasoning.cpp
        src/Graph2ReactiveReasoning.cpp
)

target_link_libraries(
        Shop_reactive PRIVATE Simulation_interface_CASE_tool
)