cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE DOLANAN_HEADER
        ../include/*.h)
file(GLOB_RECURSE DOLANAN_SOURCE
        *.cpp *.h)

add_library(dolanan STATIC ${DOLANAN_SOURCE} ${DOLANAN_HEADER})
target_include_directories(dolanan PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_include_directories(dolanan PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(dolanan PROPERTIES
        CXX_STANDARD 20)