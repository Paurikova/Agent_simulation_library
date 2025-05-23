cmake_minimum_required(VERSION 3.12)

project(frontend)

find_package(fmt 8.0.0 REQUIRED)

# Define IMGUI_NODE_EDITOR_EXTERNAL_DIR pointing to project root directory/external
get_filename_component(IMGUI_NODE_EDITOR_EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external ABSOLUTE CACHE)

# Enable solution folders in Visual Studio and Folders in Xcode
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Point CMake where to look for module files.
list(APPEND CMAKE_MODULE_PATH ${IMGUI_NODE_EDITOR_EXTERNAL_DIR}/misc/cmake-modules)

# Macro that will configure an frontend application
macro(add_frontend_executable name)
    project(${name})

    set(_Frontend_Sources
        ${ARGN}
    )

    #source_group("" FILES ${_Frontend_Sources})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${_Frontend_Sources})

    file(GLOB _Frontend_CommonResources CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/frontend/data/*")
    file(GLOB _Frontend_Resources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/data/*")
    #message(FATAL_ERROR "_Frontend_Resources = ${_Frontend_Resources}")

    set(_Frontend_Type)
    if (WIN32)
        set(_Frontend_Type WIN32)

        set(ApplicationIcon ${CMAKE_SOURCE_DIR}/frontend/Application/Support/Icon.ico)
        file(TO_NATIVE_PATH "${ApplicationIcon}" ApplicationIcon)
        string(REPLACE "\\" "\\\\" ApplicationIcon "${ApplicationIcon}")
        configure_file(
            ${CMAKE_SOURCE_DIR}/frontend/Application/Support/Resource.rc.in
            ${CMAKE_CURRENT_BINARY_DIR}/Resource.rc
        )

        source_group(TREE "${CMAKE_SOURCE_DIR}/frontend" FILES ${_Frontend_CommonResources})
        source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${_Frontend_Resources})
        list(APPEND _Frontend_Resources
            ${CMAKE_CURRENT_BINARY_DIR}/Resource.rc
            ${_Frontend_CommonResources}
        )
        source_group("resources" FILES ${CMAKE_CURRENT_BINARY_DIR}/Resource.rc)
    elseif (APPLE)
        set(_Frontend_Type MACOSX_BUNDLE)

        set_source_files_properties(${_Frontend_Resources} ${_Frontend_CommonResources} PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources/data"
        )
        set(_Frontend_Icon "${CMAKE_SOURCE_DIR}/frontend/application/support/Icon.icns")
        list(APPEND _Frontend_Resources ${_Frontend_Icon})
        set_source_files_properties(${_Frontend_Icon} PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources"
        )
    endif()

    add_executable(${name} ${_Frontend_Type} ${_Frontend_Sources} ${_Frontend_Resources} ${_Frontend_CommonResources})

    find_package(imgui REQUIRED)
    find_package(imgui_node_editor REQUIRED)
    target_link_libraries(${name} PRIVATE imgui imgui_node_editor application)

    target_link_libraries(${name} PRIVATE fmt application)
    target_link_libraries(${name} PRIVATE units)

    set(_FrontendBinDir ${CMAKE_BINARY_DIR}/bin)

    set_target_properties(${name} PROPERTIES
        FOLDER "frontend"
        RUNTIME_OUTPUT_DIRECTORY                "${_FrontendBinDir}"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${_FrontendBinDir}"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${_FrontendBinDir}"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     "${_FrontendBinDir}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${_FrontendBinDir}"
        DEBUG_POSTFIX                           _d
        RELWITHDEBINGO_POSTFIX                  _rd
        MINSIZEREL_POSTFIX                      _r
        VS_DEBUGGER_WORKING_DIRECTORY           ${_FrontendBinDir}
        MACOSX_BUNDLE_INFO_PLIST                "${CMAKE_SOURCE_DIR}/frontend/application/support/Info.plist.in"
        MACOSX_BUNDLE_BUNDLE_NAME               "${PACKAGE_NAME}"
        MACOSX_BUNDLE_GUI_IDENTIFIER            "com.sandbox.collisions"
        MACOSX_BUNDLE_LONG_VERSION_STRING       "${PACKAGE_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING      "${PACKAGE_VERSION_MAJOR}.${PACKAGE_VERSION_MINOR}"
        MACOSX_BUNDLE_ICON_FILE                 Icon.icns
    )

    add_custom_command(
        TARGET ${name}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ARGS ${_FrontendBinDir}/data
    )

    set(_ResourceRoot ${CMAKE_CURRENT_SOURCE_DIR})
    foreach(_Resource ROOT "${CMAKE_SOURCE_DIR}/frontend/data" ${_Frontend_CommonResources} ROOT "${CMAKE_CURRENT_SOURCE_DIR}/data" ${_Frontend_Resources})
        if (_Resource STREQUAL ROOT)
            set(_ResourceRoot FALSE)
            continue()
        elseif(NOT _ResourceRoot)
            set(_ResourceRoot ${_Resource})
            continue()
        endif()

        if ("${_Resource}" MATCHES "\.DS_Store$")
            list(REMOVE_ITEM _Frontend_Resources ${_Resource})
            list(REMOVE_ITEM _Frontend_CommonResources ${_Resource})
            continue()
        endif()

        file(RELATIVE_PATH _RelResource ${_ResourceRoot} ${_Resource})

        add_custom_command(
            TARGET ${name}
            PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ARGS ${_Resource} ${_FrontendBinDir}/data/${_RelResource}
        )
    endforeach()
endmacro()

# Add subdirectories (for various frontend examples)
add_subdirectory(application)
add_subdirectory(CASE_tool)