add_executable(Shop_reactive
        src/main.cpp
        src/Manager1ReactiveReasoning.cpp
        src/Customer2ReactiveReasoning.cpp
        src/Shop3ReactiveReasoning.cpp
        src/Line4ReactiveReasoning.cpp
        src/Cash5ReactiveReasoning.cpp
        src/Graph6ReactiveReasoning.cpp
)

target_link_libraries(
        Shop_reactive PRIVATE Simulation_interface_CASE_tool
)