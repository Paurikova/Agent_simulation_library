cmake_minimum_required(VERSION 3.22)

project(Agent_simulation_library)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt 8.0.0 REQUIRED)

# Include the library
add_subdirectory(library)

# Include the frontend project
add_subdirectory(frontend)

add_executable(Shop_reactive main_shop_reactive.cpp
        "simulation_models/reactive/shop/src/manager.cpp"
        "simulation_models/reactive/shop/src/customer.cpp"
        "simulation_models/reactive/shop/src/shop.cpp"
        "simulation_models/reactive/shop/src/line.cpp"
        "simulation_models/reactive/shop/src/cash.cpp"
        "simulation_models/reactive/shop/include/state_shop.h"
        "simulation_models/reactive/shop/src/graph.cpp")

add_executable(Flocking_model_reactive_stupid main_flocking_model_reactive_stupid.cpp
        "simulation_models/reactive/flocking_model_stupid/src/bird.cpp"
        "simulation_models/reactive/flocking_model_stupid/src/manager.cpp"
        "simulation_models/reactive/flocking_model_stupid/include/state_bird.h")

add_executable(Flocking_model_reactive_intelligent main_flocking_model_reactive_intelligent.cpp
        "simulation_models/reactive/flocking_model_intelligent/src/bird.cpp"
        "simulation_models/reactive/flocking_model_intelligent/src/manager.cpp"
        "simulation_models/reactive/flocking_model_intelligent/include/state_bird.h"
        "simulation_models/reactive/flocking_model_intelligent/include/state_move.h")

target_link_libraries(Agent_simulation_library fmt)

# Link with the library
target_link_libraries(Agent_simulation_library Agent_library)



# Find SFML
find_package(SFML 2.5 REQUIRED graphics window system)

# Link SFML libraries to the project
target_link_libraries(Agent_simulation_library sfml-graphics sfml-window sfml-system)