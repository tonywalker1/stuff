################################################################################
# project settings
################################################################################
cmake_minimum_required(VERSION 3.13.4)
project(stuff LANGUAGES CXX)

################################################################################
# global build settings
################################################################################
if (NOT CMAKE_CXX_FLAGS)
    message(STATUS "CMAKE_CXX_FLAGS not set. Using defaults.")
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
endif ()

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "CMAKE_BUILD_TYPE not set. Using release.")
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)

################################################################################
# display a few import an settings for debugging
################################################################################
message(STATUS "************")
message(STATUS "C++ Compiler: " ${CMAKE_CXX_COMPILER})
message(STATUS "   C++ Flags: " ${CMAKE_CXX_FLAGS})
message(STATUS "  Build Type: " ${CMAKE_BUILD_TYPE})
message(STATUS "Verbose Make: " ${CMAKE_VERBOSE_MAKEFILE})
message(STATUS " Source Path: " ${PROJECT_SOURCE_DIR})
message(STATUS "  Build Path: " ${PROJECT_BINARY_DIR})
message(STATUS "************")

################################################################################
# build subprojects
################################################################################
add_subdirectory(src)

################################################################################
# enable benchmarking and testing
################################################################################
option(STUFF_WITHOUT_TESTS "Do not build tests when ON" OFF)
if (NOT STUFF_WITHOUT_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()

option(STUFF_WITHOUT_BENCHMARKS "Do not build benchmarks when ON" OFF)
if (NOT STUFF_WITHOUT_BENCHMARKS)
    add_subdirectory(benchmarks)
endif ()

################################################################################
# cmake config
################################################################################
install(
    FILES "${PROJECT_SOURCE_DIR}/cmake/stuffConfig.cmake"
    DESTINATION "lib/cmake/stuff"
)
