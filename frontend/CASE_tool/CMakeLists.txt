add_frontend_executable(CASE_tool
        src/CASE_tool.cpp
        src/agentGenerator.cpp
        include/types_frontend.h
        utilities/builders.h
        utilities/drawing.h
        utilities/widgets.h
        utilities/builders.cpp
        utilities/drawing.cpp
        utilities/widgets.cpp
)

#Link with the library
target_link_libraries(CASE_tool PRIVATE units)