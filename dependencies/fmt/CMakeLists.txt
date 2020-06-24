FetchContent_GetProperties(fmt)

if (NOT fmt_POPULATED)
    message(STATUS "Fetching fmt v${FMT_VERSION}")

    FetchContent_Populate(fmt)

    add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()

#include(Install.cmake)