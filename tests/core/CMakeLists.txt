################################################################################
# find dependencies
################################################################################
find_package(Catch2 REQUIRED)

################################################################################
# build project
################################################################################
add_executable(stuff_core_tests
    exception_tests.cpp
    main.cpp
    string_tests.cpp
    units_tests.cpp
    )

target_link_libraries(stuff_core_tests
    Catch2::Catch2
    stuff::core
    )

include(CTest)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(stuff_core_tests)
