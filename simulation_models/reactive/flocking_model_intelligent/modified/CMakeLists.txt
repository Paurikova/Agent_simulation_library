add_executable(Flocking_model_reactive_intelligent
        src/main_flocking_model_reactive_intelligent.cpp # this could be simplified to main.cpp
        src/Bird2ReactiveReasoning.cpp
        src/Manager1ReactiveReasoning.cpp
)

target_link_libraries(
        Flocking_model_reactive_intelligent PRIVATE Simulation_interface_CASE_tool
)