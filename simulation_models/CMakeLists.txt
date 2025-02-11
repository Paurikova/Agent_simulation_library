# Find required packages
find_package(fmt 8.0.0 REQUIRED)
find_package(SFML 2.5 REQUIRED graphics window system)

# Create an interface library
add_library(Simulation_interface INTERFACE)

# Interface library that groups common properties of simulation
target_link_libraries(Simulation_interface
        PUBLIC fmt
        PUBLIC sfml-graphics
        PUBLIC sfml-window
        PUBLIC sfml-system
        PUBLIC Agent_library
        PUBLIC units
)

# Add subdirectories
add_subdirectory(petri_net)
add_subdirectory(reactive)