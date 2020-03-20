################################################################################
# find dependencies
################################################################################
find_package(Catch2 REQUIRED)

################################################################################
# build project
################################################################################
add_compile_definitions(CATCH_CONFIG_ENABLE_BENCHMARKING)
add_executable(stuff_string_benchmarks
    main.cpp
    convert_benchmarks.cpp
    )

target_link_libraries(stuff_string_benchmarks
    Catch2::Catch2
    stuff::string
    )
