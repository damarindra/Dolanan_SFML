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

option(ENABLE_IMGUI OFF)
option(ENABLE_FMT ON)

#setup all version
set(SFML_VERSION 2.5.1 CACHE STRING "Sfml version")
set(IMGUI_VERSION 1.76 CACHE STRING "Imgui version")
set(IMGUI_SFML_VERSION 2.1 CACHE STRING "ImGui-sfml version")
set(FMT_VERSION 6.2.1 CACHE STRING "fmt version")


message(STATUS "Fetching third party libraries")
#======================================

# It's nice to get stripped-down release zips instead of cloning
# a repo and checking out a tag
FetchContent_Declare(
        sfml
        URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)

FetchContent_Declare(
        imgui
        URL "https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip"
)

# Or by tag...
FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml.git
        GIT_TAG        develop
        # GIT_COMMIT 5f54b69b6aee18db846c81633f86f78c2586dded
        # ^ or like this - sometimes it's better because FetchContent won't look
        # into remote to see if branch head was updated or not - good for stable
        # tags like 'vX.X' corresponding to releases
)

# setup the git remote
FetchContent_Declare(
     fmt
     URL "https://github.com/fmtlib/fmt/archive/${FMT_VERSION}.zip"
)


add_subdirectory(imgui-sfml/dependencies/sfml)
add_subdirectory(imgui-sfml/dependencies/imgui)
add_subdirectory(imgui-sfml/dependencies/imgui-sfml)
add_subdirectory(fmt)

#======================================
message(STATUS "Fetching third party libraries done")

# setup linking

# Aliases produced inside th ImGui-SFML cmakelists.txt which is not present here, if you want to know https://github.com/eliasdaler/imgui-sfml/blob/master/CMakeLists.txt
target_link_libraries(Dolanan PUBLIC ImGui-SFML::ImGui-SFML)

# add remaining library
target_link_libraries(Dolanan
        PUBLIC sfml-audio sfml-network)

target_link_libraries(Dolanan
        PUBLIC fmt)