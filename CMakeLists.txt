#  RobotTestingFramework
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

cmake_minimum_required(VERSION 2.6)

set(PROJECTNAME rtf)
project(${PROJECTNAME})

# Pick up our CMake scripts - they are all in the conf subdirectory.
set(RTF_MODULE_PATH ${PROJECT_SOURCE_DIR}/conf)
set(CMAKE_MODULE_PATH ${RTF_MODULE_PATH})

# include version number 
include(RTFVersion)

# Make documentation target, documentation goes in
#doc subdirectory of build.
include(RTFDoc)


# Create the library 
file(GLOB folder_source ./src/*.cpp)
file(GLOB_RECURSE folder_header ./include/*.h)
source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})

include_directories(./include)
add_library(${PROJECTNAME} SHARED ${folder_source} ${folder_header} )
target_link_libraries(${PROJECTNAME})

# Create plugin
option (ENABLE_PLUGIN "Enable plugins" ON)
if (ENABLE_PLUGIN)
    add_subdirectory(extern/sharedlibpp)
endif(ENABLE_PLUGIN)

# Create examples
option (BUILD_EXAMPLES "Build examples" ON)
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif(BUILD_EXAMPLES)

