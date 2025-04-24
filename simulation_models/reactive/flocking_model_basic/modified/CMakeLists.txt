add_executable(Flocking_model_reactive_basic
        src/main_flocking_model_reactive_stupid.cpp
        src/Manager1ReactiveReasoning.cpp
        src/Bird2ReactiveReasoning.cpp
)

target_link_libraries(
        Flocking_model_reactive_basic PRIVATE Simulation_interface_CASE_tool
)