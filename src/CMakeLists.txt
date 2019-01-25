################################################################################
# find dependencies
################################################################################
find_package(Boost REQUIRED
    COMPONENTS
        filesystem
        log
        system
)
list(APPEND STUFF_LIBS ${Boost_LIBRARIES})
add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(fmt REQUIRED)
list(APPEND STUFF_LIBS fmt)

################################################################################
# build project
################################################################################
add_library(stuff SHARED
    exception.cpp
)

target_link_libraries(stuff
    PUBLIC
        ${STUFF_LIBS}
)

target_include_directories(stuff
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS stuff
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION include )
