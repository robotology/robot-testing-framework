#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>, Daniele E. Domenichelli <daniele.domenichelli@iit.it>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

cmake_minimum_required(VERSION 2.8.9)
project(RTF)

include(CMakeDependentOption)

# Pick up our CMake scripts - they are all in the conf subdirectory.
set(RTF_MODULE_PATH ${PROJECT_SOURCE_DIR}/conf)
set(CMAKE_MODULE_PATH ${RTF_MODULE_PATH})

# include version number
include(RTFVersion)

# Make documentation target, documentation goes in
#doc subdirectory of build.
include(RTFDoc)

# include some helper functions
include(InstallBasicPackageFiles)
include(GNUInstallDirs)
include (GenerateExportHeader)


# add some property to collect some information about
# what have been built
set_property(GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)
set_property(GLOBAL PROPERTY RTF_LIBS)

# add some internally used properties (not for installing or exporting)
set_property(GLOBAL PROPERTY RTF_INTERNAL_INCLUDE_DIRS)
set_property(GLOBAL PROPERTY RTF_INTERNAL_LIBS)
set_property(GLOBAL PROPERTY RTF_INTERNAL_DEFS)

# setting default compilation to release/optmized
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, recommanded options are: Debug or Release" FORCE)
endif()

# setting options
option (ENABLE_PLUGIN "Enable plugins" ON)
option (ENABLE_LUA_PLUGIN "Enable Lua plugins" OFF)
option (ENABLE_PYTHON_PLUGIN "Enable Python plugins" OFF)
option (ENABLE_RUBY_PLUGIN "Enable Ruby plugins" OFF)
option (ENABLE_MIDDLEWARE_PLUGINS "Enable middleware dependent plugins" OFF)
option (BUILD_EXAMPLES "Build examples" ON)
option (BUILD_TESTRUNNER "Build testrunner utility" ON)
option (ENABLE_WEB_LISTENER "Enable web listener" ON)


#########################################################################
# Control where libraries and executables are placed during the build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

if(BUILD_TESTRUNNER)
    set_property(CACHE ENABLE_PLUGIN PROPERTY VALUE ON)
endif()

# adding directories
add_subdirectory(extern)
add_subdirectory(src)


# examples are also used as tests
enable_testing()

add_subdirectory(examples)


# installation
set(BUILD_RTF_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/rtf/include)
set(INSTALL_RTF_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(BUILD_RTF_DLL_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/plugins/dll/include)
set(INSTALL_RTF_DLL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(BUILD_RTF_LUA_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/plugins/lua/include)
set(INSTALL_RTF_LUA_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(BUILD_RTF_PYTHON_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/plugins/python/include)
set(INSTALL_RTF_PYTHON_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(BUILD_RTF_RUBY_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/plugins/ruby/include)
set(INSTALL_RTF_RUBY_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(BUILD_RTF_YARP_INCLUDEDIR ${CMAKE_SOURCE_DIR}/src/middleware/yarp/include)
set(INSTALL_RTF_YARP_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
get_property(RTF_HAS_YARP GLOBAL PROPERTY RTF_HAS_YARP)


install_basic_package_files(${PROJECT_NAME}
                            VERSION ${RTF_VERSION}
                            COMPATIBILITY AnyNewerVersion
                            TARGETS_PROPERTY RTF_LIBS
                            EXTRA_PATH_VARS_SUFFIX DLL_INCLUDEDIR
                                                   LUA_INCLUDEDIR
                                                   PYTHON_INCLUDEDIR
                                                   RUBY_INCLUDEDIR
                                                   YARP_INCLUDEDIR)

# add uninstall target
include(AddUninstallTarget)
