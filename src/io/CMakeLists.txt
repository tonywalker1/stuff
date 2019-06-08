################################################################################
# find dependencies
################################################################################
find_package(Boost REQUIRED
    COMPONENTS
        filesystem
)

################################################################################
# build project
################################################################################
add_library(stuff_io SHARED
    filesystem.cpp
)

target_link_libraries(stuff_io
    PUBLIC
        Boost::filesystem
)

target_include_directories(stuff_io
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS stuff_io
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/stuff DESTINATION include )
