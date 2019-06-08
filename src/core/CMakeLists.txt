################################################################################
# find dependencies
################################################################################
find_package(fmt REQUIRED)

################################################################################
# build project
################################################################################
add_library(stuff_core SHARED
    exception.cpp
    string.cpp
    unicode.cpp
)

target_link_libraries(stuff_core
    PUBLIC
        fmt
)

target_include_directories(stuff_core
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS stuff_core
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/stuff DESTINATION include )
