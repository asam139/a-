cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
project(a*)

# The version number.
set (A_VERSION_MAJOR 1)
set (A_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
        "${PROJECT_SOURCE_DIR}/AConfig.h.in"
        "${PROJECT_BINARY_DIR}/AConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find SteeringBehavioursConfig.h
include_directories("${PROJECT_BINARY_DIR}")

include_directories(
        include
        include/*
        include/mathlib
        include/mathlib/*
)

file(GLOB SOURCES
        include/*.h
        source/*.cc
        source/mathlib/*.cc)
list(FILTER SOURCES EXCLUDE REGEX ".*_sse.cc$")


add_executable(steering_behaviours main.cpp AConfig.h.in ${SOURCES})

#include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(steering_behaviours
        "-framework SDL2"
        "-framework SDL2_image"
        "-framework SDL2_ttf"
        )

