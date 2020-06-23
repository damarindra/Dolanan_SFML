cmake_minimum_required(VERSION 3.16)
project(sfml_custom)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(sfml_custom main.cpp)

option(ENABLE_CONAN "Enable Conan Setup" OFF)
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
