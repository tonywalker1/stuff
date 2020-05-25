################################################################################
# find dependencies
################################################################################
find_package(date REQUIRED)
find_package(fmt REQUIRED)
find_package(Threads REQUIRED)

################################################################################
# build project
################################################################################
add_library(datetime SHARED
    conversions.cpp
    datetime.cpp
    financial.cpp
    )
set_target_properties(datetime PROPERTIES OUTPUT_NAME "stuff_datetime")
add_library(stuff::datetime ALIAS datetime)

target_compile_features(datetime
    PUBLIC
    cxx_std_17
    )

target_link_libraries(datetime
    PUBLIC
    date::date-tz
    fmt
    stuff::string
    )

target_include_directories(datetime
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BUILD_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )

################################################################################
# install project
################################################################################
install(TARGETS datetime
    EXPORT stuff_datetimeTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/stuff/datetime
    DESTINATION include/stuff
)
install(EXPORT stuff_datetimeTargets
    FILE stuff_datetimeTargets.cmake
    NAMESPACE stuff::
    DESTINATION lib/cmake/stuff_datetime
    )
install(
    FILES ${PROJECT_SOURCE_DIR}/cmake/stuff_datetimeConfig.cmake
    DESTINATION lib/cmake/stuff_datetime
)
