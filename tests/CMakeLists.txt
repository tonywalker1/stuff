################################################################################
# find dependencies
################################################################################
find_package(GTest REQUIRED)

list(APPEND STUFF_TEST_LIBS GTest::Main)
list(APPEND STUFF_TEST_LIBS stuff)

################################################################################
# build tests
################################################################################

create_test(NAME exception_tests      SRC exception.cpp      LIBS ${STUFF_TEST_LIBS})
