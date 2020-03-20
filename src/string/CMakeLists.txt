################################################################################
# find dependencies
################################################################################
find_package(fmt REQUIRED)

################################################################################
# build project
################################################################################
add_library(string SHARED
    split.cpp
    )
set_target_properties(string PROPERTIES OUTPUT_NAME "stuff_string")
add_library(stuff::string ALIAS string)

target_compile_features(string
    PUBLIC
    cxx_std_17
    )

target_link_libraries(string
    PUBLIC
    fmt
    )

target_include_directories(string
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BUILD_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )

################################################################################
# install project
################################################################################
install(TARGETS string
    EXPORT stuff_stringTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/stuff/string
    DESTINATION include/stuff/string
)
install(EXPORT stuff_stringTargets
    FILE stuff_stringTargets.cmake
    NAMESPACE stuff::
    DESTINATION lib/cmake/stuff_string
    )
install(
    FILES ${PROJECT_SOURCE_DIR}/cmake/stuff_stringConfig.cmake
    DESTINATION lib/cmake/stuff_string
)
