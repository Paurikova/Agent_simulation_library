# Create an executable
add_executable(CASE_tool
    src/CASE_tool.cpp
    src/agentGenerator.cpp
    utilities/builders.cpp
    utilities/drawing.cpp
    utilities/widgets.cpp
)

# Link with the library
target_link_libraries(CASE_TOOL PRIVATE units)
