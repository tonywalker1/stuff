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
endif()

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "CMAKE_BUILD_TYPE not set. Using release.")
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

include(GNUInstallDirs)

################################################################################
# enable benchmarking and testing
################################################################################
enable_testing()
add_custom_target(benchmark)

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
#add_subdirectory(benchmarks) # none yet...
add_subdirectory(src)
add_subdirectory(tests)
