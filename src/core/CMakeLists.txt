################################################################################
# find dependencies
################################################################################
find_package(fmt REQUIRED)

################################################################################
# build project
################################################################################
add_library(core SHARED
    exception.cpp
    )
set_target_properties(core PROPERTIES OUTPUT_NAME "stuff_core")
add_library(stuff::core ALIAS core)

target_compile_features(core
    PUBLIC
    cxx_std_17
    )

target_link_libraries(core
    PUBLIC
    fmt
    )

target_include_directories(core
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BUILD_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )

################################################################################
# install project
################################################################################
install(TARGETS core
    EXPORT stuff_coreTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/stuff/core
    DESTINATION include/stuff
)
install(EXPORT stuff_coreTargets
    FILE stuff_coreTargets.cmake
    NAMESPACE stuff::
    DESTINATION lib/cmake/stuff_core
    )
install(
    FILES ${PROJECT_SOURCE_DIR}/cmake/stuff_coreConfig.cmake
    DESTINATION lib/cmake/stuff_core
)
