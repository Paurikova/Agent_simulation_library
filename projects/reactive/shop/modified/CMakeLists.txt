add_executable(Shop_reactive_CASE_tool
        src/main_shop_reactive.cpp
        src/Manager1ReactiveReasoning.cpp
        src/Customer2ReactiveReasoning.cpp
        src/Shop3ReactiveReasoning.cpp
        src/Line5ReactiveReasoning.cpp
        src/Cash6ReactiveReasoning.cpp
        src/Graph4ReactiveReasoning.cpp
)

target_link_libraries(
        Shop_reactive_CASE_tool PRIVATE Simulation_interface_CASE_tool
)