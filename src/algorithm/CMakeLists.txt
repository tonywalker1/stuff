################################################################################
# find dependencies
################################################################################

################################################################################
# build project
################################################################################
add_library(algorithm INTERFACE)
add_library(stuff::algorithm ALIAS algorithm)

target_include_directories(algorithm INTERFACE $<INSTALL_INTERFACE:include>)

################################################################################
# install project
################################################################################
install(TARGETS algorithm
    EXPORT stuff_algorithmTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/stuff/algorithm
    DESTINATION include/stuff
)
install(EXPORT stuff_algorithmTargets
    FILE stuff_algorithmTargets.cmake
    NAMESPACE stuff::
    DESTINATION lib/cmake/stuff_algorithm
    )
install(
    FILES ${PROJECT_SOURCE_DIR}/cmake/stuff_algorithmConfig.cmake
    DESTINATION lib/cmake/stuff_algorithm
)
