cmake_minimum_required(VERSION 3.22)

project(units)

set(CMAKE_CXX_STANDARD 17)

# Add source files
set(SOURCES
        scr/fileManager.cpp
        scr/logger.cpp
        scr/uniqueDeque.cpp
        scr/configReader.cpp
)

# Create a static library
add_library(units STATIC ${SOURCES})

# Specify include directories
target_include_directories(units PUBLIC include)