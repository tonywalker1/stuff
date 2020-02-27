################################################################################
# find dependencies
################################################################################
find_package(Catch2 REQUIRED)

################################################################################
# build project
################################################################################
add_compile_definitions(CATCH_CONFIG_ENABLE_BENCHMARKING)
add_executable(stuff_core_benchmarks
    main.cpp
    string_benchmarks.cpp
    )

target_link_libraries(stuff_core_benchmarks
    Catch2::Catch2
    stuff::core
    )
