#  RobotTestingFramework
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

cmake_minimum_required(VERSION 2.6)

# Pick up our CMake scripts - they are all in the conf subdirectory.
set(RTF_MODULE_PATH ${PROJECT_SOURCE_DIR}/conf)
set(CMAKE_MODULE_PATH ${RTF_MODULE_PATH})

# include version number 
include(RTFVersion)

# Make documentation target, documentation goes in
#doc subdirectory of build.
include(RTFDoc)


# add some property to collect some information about 
# what have been built 
set_property(GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)
set_property(GLOBAL PROPERTY RTF_LIBS)

# add some internally used properties (not for intalling or exporting)
set_property(GLOBAL PROPERTY RTF_INTERNAL_INCLUDE_DIRS)
set_property(GLOBAL PROPERTY RTF_INTERNAL_LIBS)
set_property(GLOBAL PROPERTY RTF_INTERNAL_DEFS)


# setting options
option (ENABLE_PLUGIN "Enable plugins" ON)
option (BUILD_EXAMPLES "Build examples" ON)
option (BUILD_TESTRUNNER "Build testrunner utility" ON)

if(BUILD_TESTRUNNER)
    set(ENABLE_PLUGIN ON)
endif()

# adding directories
add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(examples)

