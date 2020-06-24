FetchContent_GetProperties(entt)

if (NOT entt_POPULATED)
    message(STATUS "Fetching entt v${ENTT_VERSION}")

    FetchContent_Populate(entt)

    add_subdirectory(${entt_SOURCE_DIR} ${entt_BINARY_DIR})
endif ()