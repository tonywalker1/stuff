################################################################################
# find dependencies
################################################################################
find_package(Catch2 REQUIRED)

################################################################################
# build project
################################################################################
add_executable(stuff_io_tests
    filesystem.cpp
    main.cpp
)

target_link_libraries(stuff_io_tests
    Catch2::Catch2
    stuff_core
    stuff_io
)

include(CTest)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(stuff_io_tests)
