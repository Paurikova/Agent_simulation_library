add_executable(Flocking_model_reactive_stupid
        src/main_flocking_model_reactive_stupid.cpp # this could be simplified to main.cpp
        src/bird.cpp
        src/manager.cpp
)

target_link_libraries(
        Flocking_model_reactive_stupid PRIVATE Simulation_interface
)