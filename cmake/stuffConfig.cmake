################################################################################
# error checking
################################################################################
if (NOT stuff_FIND_COMPONENTS)
    set(stuff_NOT_FOUND_MESSAGE "The stuff package requires at least one component")
    set(stuff_FOUND False)
    return()
endif ()

################################################################################
# handle find_package options
################################################################################
set(stuff_required_option)
if (stuff_FIND_REQUIRED)
    set(stuff_required_option REQUIRED)
endif ()
set(stuff_quiet_option)
if (stuff_FIND_QUIET)
    set(stuff_quiet_option QUIET)
endif ()

################################################################################
# run find_package for each component
################################################################################
foreach (module ${stuff_FIND_COMPONENTS})
    message(STATUS "--> finding ${module}")
    find_package(stuff_${module}
        ${stuff_required_option}
        ${stuff_quiet_option}
        )
endforeach ()
