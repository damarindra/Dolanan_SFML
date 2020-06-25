# chipmunk little bit hassle, the cmake command inside chipmunkpp is not enough. it needs to submodule chipmunk
# using chipmunkpp wrapper https://github.com/jhasse/chipmunkpp/
# careful, since this wrapper is handwriting, no autogenerate. match the chipmunk version as described in the repo
#project(cp)
find_package(Git QUIET)

if(GIT_FOUND)
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/chipmunkpp)
        execute_process(COMMAND ${GIT_EXECUTABLE} clone --branch 6.2.x https://github.com/jhasse/chipmunkpp.git
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()

    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/chipmunkpp)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/chipmunkpp)
endif()

#if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/repo/CMakeLists.txt")
#    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
#endif()
#
#add_subdirectory(chipmunk)
#
#set(chipmunkpp_VERSION 6.2.x)
#
#FetchContent_Declare(
#        chipmunkpp
#        URL https://github.com/jhasse/chipmunkpp/archive/${chipmunkpp_VERSION}.zip
##        GIT_TAG        chipmunkpp_VERSION
#)
#
#FetchContent_GetProperties(chipmunkpp)
#
#if (NOT chipmunkpp_POPULATED)
#    message(STATUS "Fetching chipmunkpp ${chipmunkpp_VERSION}")
#
#    FetchContent_Populate(chipmunkpp)
#
#    file(GLOB SOURCES ${chipmunkpp_SOURCE_DIR}/src/*.cpp ${chipmunkpp_SOURCE_DIR}/src/chipmunkpp/*.cpp)
#    add_library(cp STATIC ${SOURCES})
#    target_include_directories(cp PUBLIC
#            ${chipmunk_SOURCE_DIR}/include/chipmunk
#            ${chipmunk_SOURCE_DIR}/src
#            )
#
#    target_link_libraries(cp PUBLIC chipmunk_static)
#
#endif ()