cmake_minimum_required(VERSION 3.16)
project(game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(game main.cpp)

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


add_subdirectory(imgui-sfml)

# Aliases produced inside th ImGui-SFML cmakelists.txt which is not present here, if you want to know https://github.com/eliasdaler/imgui-sfml/blob/master/CMakeLists.txt
target_link_libraries(game PUBLIC ImGui-SFML::ImGui-SFML)

# add remaining sfml library
target_link_libraries(game PUBLIC sfml-audio sfml-network)

include(imgui-sfml/Install.cmake)