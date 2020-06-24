FetchContent_GetProperties(box2d)

set(BOX2D_BUILD_EXAMPLES OFF)
#set(BOX2D_INSTALL ON CACHE BOOL "install box2d")
#set(BOX2D_BUILD_SHARED OFF CACHE BOOL "build box2d shared")
#set(BOX2D_BUILD_STATIC ON)


if (NOT box2d_POPULATED)
    message(STATUS "Fetching box2d v${BOX2D_VERSION}")


    FetchContent_Populate(box2d)

    add_subdirectory(${box2d_SOURCE_DIR} ${box2d_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()

