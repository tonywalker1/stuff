################################################################################
# find dependencies
################################################################################
find_package(Catch2 REQUIRED)

################################################################################
# build project
################################################################################
add_executable(stuff_string_tests
    main.cpp
    convert.cpp
    split_tests.cpp
    )

target_link_libraries(stuff_string_tests
    Catch2::Catch2
    stuff::string
    )

include(CTest)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(stuff_string_tests)
