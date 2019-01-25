################################################################################
# project settings
################################################################################
cmake_minimum_required(VERSION 3.7.2)
project(stuff LANGUAGES CXX)

################################################################################
# global build settings
################################################################################
if (NOT CMAKE_CXX_FLAGS)
    message(STATUS "CMAKE_CXX_FLAGS not set. Using defaults.")
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
endif()

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "CMAKE_BUILD_TYPE not set. Using release.")
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

include(GNUInstallDirs)

################################################################################
# enable benchmarking and testing
################################################################################
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(create_benchmark)
add_custom_target(benchmark)

include(create_test)
enable_testing()

################################################################################
# display a few import an settings for debugging
################################################################################
message(STATUS "************")
message(STATUS "C++ Compiler: " ${CMAKE_CXX_COMPILER})
message(STATUS "C++ Standard: " ${CMAKE_CXX_STANDARD})
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
add_subdirectory(tests)
