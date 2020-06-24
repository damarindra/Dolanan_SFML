cmake_minimum_required(VERSION 3.16)
project(Dolanan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

# sfml linker specific
add_link_options(-static-libgcc -static-libstdc++)

add_executable(Dolanan main.cpp)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which is a good idea if any #define's change
    #
    # consider breaking this out per project as necessary
    target_precompile_headers(
            Dolanan
            INTERFACE
            <vector>
            <string>
            <map>
            <utility>)
endif()

# Add All Dependencies
add_subdirectory(dependencies)