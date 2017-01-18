#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>, Daniele E. Domenichelli <daniele.domenichelli@iit.it>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


include(CMakeDependentOption)

# enable RPATH
option(ENABLE_RPATH "Enable RPATH for this library" ON)
mark_as_advanced(ENABLE_RPATH)
include(AddInstallRPATHSupport)
add_install_rpath_support(BIN_DIRS "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}"
                          LIB_DIRS "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
                          DEPENDS ENABLE_RPATH
                          USE_LINK_PATH)

# add some property to collect some information about
# what have been built
set_property(GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)
set_property(GLOBAL PROPERTY RTF_LIBS)

# add some internally used properties (not for installing or exporting)
set_property(GLOBAL PROPERTY RTF_INTERNAL_INCLUDE_DIRS)
set_property(GLOBAL PROPERTY RTF_INTERNAL_LIBS)
set_property(GLOBAL PROPERTY RTF_INTERNAL_DEFS)

# setting options
option(ENABLE_PLUGIN "Enable plugins" ON)
option(ENABLE_LUA_PLUGIN "Enable Lua plugins" OFF)
option(ENABLE_PYTHON_PLUGIN "Enable Python plugins" OFF)
option(ENABLE_RUBY_PLUGIN "Enable Ruby plugins" OFF)
option(ENABLE_MIDDLEWARE_PLUGINS "Enable middleware dependent plugins" OFF)
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTRUNNER "Build testrunner utility" ON)
#option(BUILD_TESTS "Build tests" ON)
option(ENABLE_WEB_LISTENER "Enable web listener" ON)


#########################################################################
# Control where libraries and executables are placed during the build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

if(BUILD_TESTRUNNER)
    set_property(CACHE ENABLE_PLUGIN PROPERTY VALUE ON)
endif()

# setting default compilation to release/optmized
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, recommanded options are: Debug or Release" FORCE)
endif()


if(CMAKE_COMPILER_IS_GNUCXX)
    option(ENABLE_CODE_PROFILING "Enable code coverage profiling (only for GNUCXX)" OFF)
    mark_as_advanced(ENABLE_CODE_PROFILING)
    if(ENABLE_CODE_PROFILING)
        set(CMAKE_BUILD_TYPE "Coverage" CACHE STRING "Choose the type of build, recommanded options are: Debug or Release" FORCE)
        include(CodeCoverage)
        setup_target_for_coverage(${PROJECT_NAME}_coverage ctest coverage)
    endif()

endif()

