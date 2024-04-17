cmake_minimum_required(VERSION 3.22)

project(Agent_simulation_library)

set(CMAKE_CXX_STANDARD 17)

add_executable(Agent_simulation_library main.cpp)
# Include the frontend project
add_subdirectory(library_test)