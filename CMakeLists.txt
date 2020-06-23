cmake_minimum_required(VERSION 3.16)
project(sfml_custom)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(sfml_custom main.cpp)

option(ENABLE_CONAN "Enable Conan Setup" OFF)
message(${CMAKE_SYSTEM_NAME})
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

        message(gfdsgfds)
    else()
        set(SFML_STATIC_LIBRARIES YES)
        set(SFML_ROOT ../SFML-2.5.1 CACHED PATH "SFML Root folder")
        find_package(SFML
                COMPONENTS audio graphics system window network
                PATHS ${SFML_ROOT}
                REQUIRED)

        if(SFML_FOUND)
            target_link_libraries(sfml_custom PRIVATE sfml-main sfml-audio sfml-system sfml-window sfml-network sfml-graphics)
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
