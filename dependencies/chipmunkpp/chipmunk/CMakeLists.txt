# using chipmunkpp wrapper https://github.com/jhasse/chipmunkpp/
# careful, since this wrapper is handwriting, no autogenerate. match the chipmunk version as described in the repo
#
set(BUILD_DEMOS OFF CACHE BOOL "Chipmunk Demos" FORCE)
set(BUILD_SHARED OFF CACHE BOOL "Build and install the shared library" FORCE)

FetchContent_Declare(
        chipmunk
        GIT_REPOSITORY https://github.com/slembcke/Chipmunk2D.git
        GIT_TAG        Chipmunk-6.2.2
)

FetchContent_GetProperties(chipmunk)

if (NOT chipmunk_POPULATED)
    message(STATUS "Fetching chipmunk ffc6a1bf0f67e251b3df8a7df75da7716c0116b2")

    FetchContent_Populate(chipmunk)

    add_subdirectory(${chipmunk_SOURCE_DIR} ${chipmunk_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()