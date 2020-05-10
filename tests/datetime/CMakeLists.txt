################################################################################
# find dependencies
################################################################################
find_package(Catch2 REQUIRED)

################################################################################
# build project
################################################################################
add_executable(stuff_datetime_tests
    main.cpp
    conversions_tests.cpp
    )

target_link_libraries(stuff_datetime_tests
    Catch2::Catch2
    stuff::core
    stuff::datetime
    )

include(CTest)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(stuff_datetime_tests)
