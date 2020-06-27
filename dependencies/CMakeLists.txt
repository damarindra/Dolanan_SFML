# This is an example of how to use FetchContent to easily
# manage 3rd-party dependencies
# First, check out src/CMakeLists.txt - it's really simple!
# Then, check out dependencies directory, it get a bit more complex
# there, but you'll see how it goes
#
# Options:
# * USE_SYSTEM_DEPS - try to find dependencies using find_package (OFF by default)
# * LINK_DEPS_STATIC - link to dependencies statically (ON by default)
#
cmake_minimum_required(VERSION 3.16)

include(FetchContent)

option(USE_SYSTEM_DEPS CACHE OFF)
option(LINK_DEPS_STATIC CACHE ON)

# Don't build shared libs if we want to link to deps statically
if(LINK_DEPS_STATIC)
    set(BUILD_SHARED_LIBS OFF)
else()
    set(BUILD_SHARED_LIBS ON)
endif()

option(ENABLE_IMGUI CACHE ON)
option(ENABLE_FMT CACHE ON)
option(ENABLE_SPDLOG CACHE ON)
option(ENABLE_BOX2D CACHE OFF)
option(ENABLE_ENTT CACHE ON)
option(ENABLE_CHIPMUNK CACHE OFF)

#setup all version
set(SFML_VERSION 2.5.1 CACHE STRING "Sfml version")
set(IMGUI_VERSION v1.76 CACHE STRING "Imgui version")
set(IMGUI_SFML_VERSION v2.1 CACHE STRING "Imgui-Sfml version")
set(FMT_VERSION 6.2.1 CACHE STRING "fmt version")
set(SPDLOG_VERSION v1.6.1 CACHE STRING "spdlog version")
set(BOX2D_VERSION master CACHE STRING "box2d version")
set(ENTT_VERSION v3.4.0 CACHE STRING "EnTT version")


message(STATUS "Fetching third party libraries")
#======================================

# It's nice to get stripped-down release zips instead of cloning
# a repo and checking out a tag
FetchContent_Declare(
        sfml
        URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)
add_subdirectory(sfml)


if (ENABLE_IMGUI)
    FetchContent_Declare(
            imgui
            URL "https://github.com/ocornut/imgui/archive/${IMGUI_VERSION}.zip"
    )
    add_subdirectory(imgui)

    # Or by tag...
    FetchContent_Declare(
            imgui-sfml
            URL "https://github.com/eliasdaler/imgui-sfml/archive/${IMGUI_SFML_VERSION}.zip"
#            GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml.git
#            GIT_TAG        develop
            # GIT_COMMIT 5f54b69b6aee18db846c81633f86f78c2586dded
            # ^ or like this - sometimes it's better because FetchContent won't look
            # into remote to see if branch head was updated or not - good for stable
            # tags like 'vX.X' corresponding to releases
    )
    add_subdirectory(imgui-sfml)

    # Aliases produced inside th ImGui-SFML cmakelists.txt which is not present here, if you want to know https://github.com/eliasdaler/imgui-sfml/blob/master/CMakeLists.txt
    target_link_libraries(dolanan PUBLIC ImGui-SFML::ImGui-SFML)
else()
    # add sfml library
    target_link_libraries(dolanan PUBLIC sfml-system sfml-graphics sfml-window)
endif ()

if (ENABLE_FMT)
    # setup the git remote
    FetchContent_Declare(
         fmt
         URL "https://github.com/fmtlib/fmt/archive/${FMT_VERSION}.zip"
    )
    add_subdirectory(fmt)

    target_link_libraries(dolanan
            PUBLIC fmt)

endif ()


if (ENABLE_SPDLOG)
    # setup the git remote
    FetchContent_Declare(
            spdlog
            URL "https://github.com/gabime/spdlog/archive/${SPDLOG_VERSION}.zip"
    )
    add_subdirectory(spdlog)

    target_link_libraries(dolanan
            PUBLIC spdlog)

endif ()

if (ENABLE_ENTT)
    # setup the git remote
    FetchContent_Declare(
            entt
            URL "https://github.com/skypjack/entt/archive/${ENTT_VERSION}.zip"
    )
    add_subdirectory(entt)

    target_link_libraries(dolanan
            PUBLIC EnTT)

endif ()


if (ENABLE_BOX2D)
    # setup the git remote
    FetchContent_Declare(
            box2d
            URL "https://github.com/erincatto/box2d/archive/${BOX2D_VERSION}.zip"
    )
    add_subdirectory(box2d)

    target_link_libraries(dolanan
            PUBLIC box2d)

endif ()

# I give up with chipmunk, it is so stupid how the cmake included in chipmunkpp work, wait until the author realize
# fetchContent is god giver
#if(ENABLE_CHIPMUNK)
#    add_subdirectory(chipmunkpp)
#
#    target_link_directories(Dolanan
#            PUBLIC chipmunkpp)
#endif()


#======================================
message(STATUS "Fetching third party libraries done")

# setup linking

# add remaining library
target_link_libraries(dolanan
        PUBLIC sfml-audio sfml-network)
