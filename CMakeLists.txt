cmake_minimum_required(VERSION 3.22)

project(Agent_simulation_library)

set(CMAKE_CXX_STANDARD 17)

# Find required packages
find_package(fmt 8.0.0 REQUIRED)
find_package(SFML 2.5 REQUIRED graphics window system)

# Create executables
add_executable(Shop_reactive main_shop_reactive.cpp
        simulation_models/reactive/shop/src/manager.cpp
        simulation_models/reactive/shop/src/customer.cpp
        simulation_models/reactive/shop/src/shop.cpp
        simulation_models/reactive/shop/src/line.cpp
        simulation_models/reactive/shop/src/cash.cpp
        simulation_models/reactive/shop/include/state_shop.h
        simulation_models/reactive/shop/src/graph.cpp
)

add_executable(Shop_petri_net main_shop_petri_net.cpp
        simulation_models/petri_net/shop/src/manager.cpp
        simulation_models/petri_net/shop/src/customer.cpp
        simulation_models/petri_net/shop/src/shop.cpp
        simulation_models/petri_net/shop/src/line.cpp
        simulation_models/petri_net/shop/src/cash.cpp
        simulation_models/petri_net/shop/include/state_shop.h
        simulation_models/petri_net/shop/src/graph.cpp
)

add_executable(Flocking_model_reactive_stupid main_flocking_model_reactive_stupid.cpp
        simulation_models/reactive/flocking_model_stupid/src/bird.cpp
        simulation_models/reactive/flocking_model_stupid/src/manager.cpp
        simulation_models/reactive/flocking_model_stupid/include/state_bird.h
)

add_executable(Flocking_model_reactive_intelligent main_flocking_model_reactive_intelligent.cpp
        simulation_models/reactive/flocking_model_intelligent/src/bird.cpp
        simulation_models/reactive/flocking_model_intelligent/src/manager.cpp
        simulation_models/reactive/flocking_model_intelligent/include/state_bird.h
        simulation_models/reactive/flocking_model_intelligent/include/state_move.h
)

# Include the frontend project
add_subdirectory(frontend)
add_subdirectory(library)
add_subdirectory(units)

# Link libraries to executables
target_link_libraries(Shop_reactive
        PRIVATE fmt
        PRIVATE sfml-graphics
        PRIVATE sfml-window
        PRIVATE sfml-system
        PRIVATE Agent_library
        PRIVATE units
)

target_link_libraries(Shop_petri_net
        PRIVATE fmt
        PRIVATE sfml-graphics
        PRIVATE sfml-window
        PRIVATE sfml-system
        PRIVATE Agent_library
        PRIVATE units
)

target_link_libraries(Flocking_model_reactive_stupid
        PRIVATE fmt
        PRIVATE sfml-graphics
        PRIVATE sfml-window
        PRIVATE sfml-system
        PRIVATE Agent_library
        PRIVATE units
)

target_link_libraries(Flocking_model_reactive_intelligent
        PRIVATE fmt
        PRIVATE sfml-graphics
        PRIVATE sfml-window
        PRIVATE sfml-system
        PRIVATE Agent_library
        PRIVATE units
)

