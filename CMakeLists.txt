cmake_minimum_required(VERSION 3.22)

project(Agent_simulation_library)

set(CMAKE_CXX_STANDARD            17)
set(CMAKE_CXX_STANDARD_REQUIRED   YES)

add_subdirectory(units)
add_subdirectory(frontend)
add_subdirectory(library)
add_subdirectory(simulation_models)
add_subdirectory(projects)