################################################################################
# find dependencies
################################################################################

################################################################################
# build project
################################################################################
add_library(unicode SHARED
    convert.cpp
    detect.cpp
    )
set_target_properties(unicode PROPERTIES OUTPUT_NAME "stuff_unicode")
add_library(stuff::unicode ALIAS unicode)

target_compile_features(unicode
    PUBLIC
    cxx_std_17
    )

target_link_libraries(unicode
    PUBLIC
    )

target_include_directories(unicode
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BUILD_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )

################################################################################
# install project
################################################################################
install(TARGETS unicode
    EXPORT stuff_unicodeTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/stuff/unicode
    DESTINATION include/stuff
)
install(EXPORT stuff_unicodeTargets
    FILE stuff_unicodeTargets.cmake
    NAMESPACE stuff::
    DESTINATION lib/cmake/stuff_unicode
    )
install(
    FILES ${PROJECT_SOURCE_DIR}/cmake/stuff_unicodeConfig.cmake
    DESTINATION lib/cmake/stuff_unicode
)
