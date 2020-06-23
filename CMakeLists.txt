cmake_minimum_required(VERSION 3.16)
project(sfml_custom)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(sfml_custom main.cpp)


# Change this directory if you haven't setup sfml at environment variable
set(SFML_DIR "../SFML-2.5.1" CACHE PATH "SFML Root folder")
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui CACHE PATH "Imgui Root folder")

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${SFML_DIR})
# add ImGui build folder
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/imgui-sfml/CMakeFiles/Export/lib/cmake/ImGui-SFML)

option(ENABLE_IMGUI "Enable Imgui Support" ON)

# Conan is kind of deprecated, might me remove later
option(ENABLE_CONAN "Enable Conan Setup" OFF)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if(ENABLE_CONAN)
        if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
            message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
            file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                    "${CMAKE_BINARY_DIR}/conan.cmake")
        endif()

        include(${CMAKE_BINARY_DIR}/conan.cmake)

        conan_add_remote(NAME bincrafters
                URL https://api.bintray.com/conan/bincrafters/public-conan)

        conan_cmake_run(
                REQUIRES
                imgui-sfml/2.1@bincrafters/stable
                BASIC_SETUP
                BUILD missing
        )

        target_link_libraries(sfml_custom
                PRIVATE ${CONAN_LIBS})

    else()
        set(SFML_STATIC_LIBRARIES YES)
        find_package(SFML
                COMPONENTS audio graphics system window network
                REQUIRED)

        if(SFML_FOUND)
            target_link_libraries(sfml_custom PRIVATE sfml-main sfml-audio sfml-system sfml-window sfml-network sfml-graphics)
        endif()

        if(ENABLE_IMGUI)
            # build imgui-sfml
            add_subdirectory(imgui-sfml)

            find_package(ImGui-SFML REQUIRED)
            target_link_libraries(sfml_custom PRIVATE ImGui-SFML::ImGui-SFML)
        endif()

    endif()
endif()


# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which is a good idea if any #define's change
    #
    # consider breaking this out per project as necessary
    target_precompile_headers(
            sfml_custom
            INTERFACE
            <vector>
            <string>
            <map>
            <utility>)
endif()
