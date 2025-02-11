# Create a static library
add_library(units STATIC
        scr/fileManager.cpp
        scr/logger.cpp
        scr/uniqueDeque.cpp
        scr/configReader.cpp
)

# Specify include directories
target_include_directories(units PUBLIC include)