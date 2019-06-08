################################################################################
# find dependencies
################################################################################
find_package(Catch2 REQUIRED)

################################################################################
# build project
################################################################################
add_executable(stuff_core_tests
    exception.cpp
    main.cpp
    string.cpp
)

target_link_libraries(stuff_core_tests
    Catch2::Catch2
    stuff_core
)

include(CTest)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(stuff_core_tests)
