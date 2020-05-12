################################################################################
# find dependencies
################################################################################
find_package(Boost REQUIRED
    COMPONENTS
    filesystem
    iostreams
    system
    )
find_package(range-v3 REQUIRED)

################################################################################
# build project
################################################################################
add_library(io SHARED
    filesystem.cpp
    )
set_target_properties(io PROPERTIES OUTPUT_NAME "stuff_io")
add_library(stuff::io ALIAS io)

target_compile_features(io
    PUBLIC
    cxx_std_17
    )

target_link_libraries(io
    PUBLIC
    Boost::filesystem
    Boost::iostreams
    Boost::system
    range-v3::range-v3
    )

target_include_directories(io
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BUILD_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )

################################################################################
# install project
################################################################################
install(TARGETS io
    EXPORT stuff_ioTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/stuff/io
    DESTINATION include/stuff
)
install(EXPORT stuff_ioTargets
    FILE stuff_ioTargets.cmake
    NAMESPACE stuff::
    DESTINATION lib/cmake/stuff_io
    )
install(
    FILES ${PROJECT_SOURCE_DIR}/cmake/stuff_ioConfig.cmake
    DESTINATION lib/cmake/stuff_io
)
