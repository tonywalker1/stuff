################################################################################
# find dependencies
################################################################################

################################################################################
# build project
################################################################################
add_library(container INTERFACE)
add_library(stuff::container ALIAS container)

target_include_directories(container INTERFACE $<INSTALL_INTERFACE:include>)

################################################################################
# install project
################################################################################
install(TARGETS container
    EXPORT stuff_containerTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/stuff/container
    DESTINATION include/stuff
)
install(EXPORT stuff_containerTargets
    FILE stuff_containerTargets.cmake
    NAMESPACE stuff::
    DESTINATION lib/cmake/stuff_container
    )
install(
    FILES ${PROJECT_SOURCE_DIR}/cmake/stuff_containerConfig.cmake
    DESTINATION lib/cmake/stuff_container
)
