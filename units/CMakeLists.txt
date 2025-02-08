cmake_minimum_required(VERSION 3.22)

project(Units)

set(CMAKE_CXX_STANDARD 17)

# Add all source files for the library
set(UNITS_SOURCE
        scr/uniqueDeque.cpp
        scr/logger.cpp
        scr/fileManager.cpp
)

# Create the library
add_library(units ${UNITS_SOURCE})

# Include directories if needed
target_include_directories(units PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})