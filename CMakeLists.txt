cmake_minimum_required(VERSION 3.16)
project(sample)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

# sfml linker specific
add_link_options(-static-libgcc -static-libstdc++)


#add_library(dolanan
#        include/core/GameCycle.h include/core/Game.h
#        src/component/Transform.cpp include/component/Transform.h
#        src/core/Math.h src/core/Game.cpp)
#set_target_properties(dolanan PROPERTIES LINKER_LANGUAGE CXX)
#
#add_library(cute_c2 src/collision2d/cute_c2.h)
#set_target_properties(cute_c2 PROPERTIES LINKER_LANGUAGE CXX)
#target_link_libraries(dolanan PRIVATE cute_c2)

add_subdirectory(src)

# Add All Dependencies
add_subdirectory(dependencies)


add_executable(sample main.cpp)


target_link_libraries(sample
        PUBLIC dolanan)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
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
endif ()