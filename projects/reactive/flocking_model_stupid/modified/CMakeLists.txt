add_executable(Flocking_model_reactive_stupid_CASE_tool
        src/main_flocking_model_reactive_stupid.cpp
        src/Manager1ReactiveReasoning.cpp
        src/Bird2ReactiveReasoning.cpp
)

target_link_libraries(
        Flocking_model_reactive_stupid_CASE_tool PRIVATE Simulation_interface_CASE_tool
)