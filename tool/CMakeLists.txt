cmake_minimum_required(VERSION 3.12)

project(tool)

# Define IMGUI_NODE_EDITOR_ROOT_DIR pointing to project root directory
#ZMENA TERAZ
get_filename_component(IMGUI_NODE_EDITOR_ROOT_DIR ${CMAKE_SOURCE_DIR} ABSOLUTE CACHE)
# Enable solution folders in Visual Studio and Folders in Xcode
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Point CMake where to look for module files.
#ZMENA TERAZ /..
list(APPEND CMAKE_MODULE_PATH ${IMGUI_NODE_EDITOR_ROOT_DIR}/misc/cmake-modules)
# Node editor use C++14
set(CMAKE_CXX_STANDARD            14)
set(CMAKE_CXX_STANDARD_REQUIRED   YES)

# Macro that will configure an tool application
macro(add_tool_executable name)
    project(${name})

    set(_tool_Sources
        ${ARGN}
    )

    #source_group("" FILES ${_tool_Sources})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${_tool_Sources})

    #ZMENA
    file(GLOB _tool_CommonResources CONFIGURE_DEPENDS "${IMGUI_NODE_EDITOR_ROOT_DIR}/tool/data/*")
    file(GLOB _tool_Resources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/data/*")
    #message(FATAL_ERROR "_tool_Resources = ${_tool_Resources}")

    set(_tool_Type)
    if (WIN32)
        set(_tool_Type WIN32)

        #ZMENA
        set(ApplicationIcon ${IMGUI_NODE_EDITOR_ROOT_DIR}/tool/Application/Support/Icon.ico)
        file(TO_NATIVE_PATH "${ApplicationIcon}" ApplicationIcon)
        string(REPLACE "\\" "\\\\" ApplicationIcon "${ApplicationIcon}")
        configure_file(
                #ZMENA
            ${IMGUI_NODE_EDITOR_ROOT_DIR}/tool/Application/Support/Resource.rc.in
            ${CMAKE_CURRENT_BINARY_DIR}/Resource.rc
        )
        #ZMENA
        source_group(TREE "${IMGUI_NODE_EDITOR_ROOT_DIR}/tool" FILES ${_tool_CommonResources})
        source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${_tool_Resources})
        list(APPEND _tool_Resources
            ${CMAKE_CURRENT_BINARY_DIR}/Resource.rc
            ${_tool_CommonResources}
        )
        source_group("resources" FILES ${CMAKE_CURRENT_BINARY_DIR}/Resource.rc)
    elseif (APPLE)
        set(_tool_Type MACOSX_BUNDLE)

        set_source_files_properties(${_tool_Resources} ${_tool_CommonResources} PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources/data"
        )
        #ZMENA
        set(_tool_Icon "${IMGUI_NODE_EDITOR_ROOT_DIR}/tool/application/support/Icon.icns")
        list(APPEND _tool_Resources ${_tool_Icon})
        set_source_files_properties(${_tool_Icon} PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources"
        )
    endif()

    add_executable(${name} ${_tool_Type} ${_tool_Sources} ${_tool_Resources} ${_tool_CommonResources})

    find_package(imgui REQUIRED)
    find_package(imgui_node_editor REQUIRED)
    target_link_libraries(${name} PRIVATE imgui imgui_node_editor application)

    set(_toolBinDir ${CMAKE_BINARY_DIR}/bin)

    set_target_properties(${name} PROPERTIES
            #ZMENA
        FOLDER "tool"
        RUNTIME_OUTPUT_DIRECTORY                "${_toolBinDir}"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${_toolBinDir}"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${_toolBinDir}"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     "${_toolBinDir}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${_toolBinDir}"
        DEBUG_POSTFIX                           _d
        RELWITHDEBINGO_POSTFIX                  _rd
        MINSIZEREL_POSTFIX                      _r
        VS_DEBUGGER_WORKING_DIRECTORY           ${_toolBinDir}
            #ZMENA
        MACOSX_BUNDLE_INFO_PLIST                "${IMGUI_NODE_EDITOR_ROOT_DIR}/tool/application/support/Info.plist.in"
        MACOSX_BUNDLE_BUNDLE_NAME               "${PACKAGE_NAME}"
        MACOSX_BUNDLE_GUI_IDENTIFIER            "com.sandbox.collisions"
        MACOSX_BUNDLE_LONG_VERSION_STRING       "${PACKAGE_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING      "${PACKAGE_VERSION_MAJOR}.${PACKAGE_VERSION_MINOR}"
        MACOSX_BUNDLE_ICON_FILE                 Icon.icns
    )

    add_custom_command(
        TARGET ${name}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ARGS ${_toolBinDir}/data
    )

    set(_ResourceRoot ${CMAKE_CURRENT_SOURCE_DIR})
    #ZMENA
    foreach(_Resource ROOT "${IMGUI_NODE_EDITOR_ROOT_DIR}/tool/data" ${_tool_CommonResources} ROOT "${CMAKE_CURRENT_SOURCE_DIR}/data" ${_tool_Resources})
        if (_Resource STREQUAL ROOT)
            set(_ResourceRoot FALSE)
            continue()
        elseif(NOT _ResourceRoot)
            set(_ResourceRoot ${_Resource})
            continue()
        endif()

        if ("${_Resource}" MATCHES "\.DS_Store$")
            list(REMOVE_ITEM _tool_Resources ${_Resource})
            list(REMOVE_ITEM _tool_CommonResources ${_Resource})
            continue()
        endif()

        file(RELATIVE_PATH _RelResource ${_ResourceRoot} ${_Resource})

        add_custom_command(
            TARGET ${name}
            PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ARGS ${_Resource} ${_toolBinDir}/data/${_RelResource}
        )
    endforeach()

endmacro()

add_subdirectory(application)
add_subdirectory(CASE_tool)
