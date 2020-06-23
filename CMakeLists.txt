cmake_minimum_required(VERSION 3.16)
project(game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(game main.cpp)


# Change this directory if you haven't setup sfml at environment variable
set(SFML_DIR "../SFML-2.5.1" CACHE PATH "SFML Root folder")
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui CACHE PATH "Imgui Root folder")

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${SFML_DIR})
# add ImGui build folder
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/imgui-sfml/CMakeFiles/Export/lib/cmake/ImGui-SFML)

option(ENABLE_IMGUI "Enable Imgui Support" ON)

set(SFML_STATIC_LIBRARIES YES)
find_package(SFML
        COMPONENTS audio graphics system window network
        REQUIRED)

if(SFML_FOUND)
    target_link_libraries(game PUBLIC sfml-audio sfml-system sfml-window sfml-network sfml-graphics)
endif()

if(ENABLE_IMGUI)
    # build imgui-sfml
    add_subdirectory(imgui-sfml)

    find_package(ImGui-SFML REQUIRED)
    target_link_libraries(game PUBLIC ImGui-SFML::ImGui-SFML)
endif()

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which is a good idea if any #define's change
    #
    # consider breaking this out per project as necessary
    target_precompile_headers(
            game
            INTERFACE
            <vector>
            <string>
            <map>
            <utility>)
endif()
