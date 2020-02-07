################################################################################
# find dependencies
################################################################################
find_package(Catch2 REQUIRED)

################################################################################
# build project
################################################################################
add_executable(stuff_algorithm_tests
    random_tests.cpp
    main.cpp
)

target_link_libraries(stuff_algorithm_tests
    PUBLIC
        Catch2::Catch2
        stuff::core
)

include(CTest)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(stuff_algorithm_tests)
