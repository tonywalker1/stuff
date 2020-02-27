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
    PUBLIC
    Catch2::Catch2
    stuff::core
    stuff::io
    )

include(CTest)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(stuff_io_tests)
