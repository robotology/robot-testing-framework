#  Sharedlib++
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

cmake_minimum_required(VERSION 2.6)

project(RTF_sharedlib++)

set_property(GLOBAL APPEND PROPERTY RTF_TREE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
get_property(RTF_TREE_INCLUDE_DIRS GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)


# Create the library 
file(GLOB folder_source ./src/*.cpp)
file(GLOB_RECURSE folder_header ./include/*.h)
source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})

include_directories(${RTF_TREE_INCLUDE_DIRS})
add_library(RTF_sharedlib++ SHARED ${folder_source} ${folder_header} )

if(NOT WIN32)
  target_link_libraries(RTF_sharedlib++ dl)
endif()

# choose which header files should be installed 
file(GLOB RTF_SHLIB_HEADERS ./include/*.h)
set_property(TARGET RTF_sharedlib++ PROPERTY PUBLIC_HEADER ${RTF_SHLIB_HEADERS})

install(TARGETS RTF_sharedlib++
        EXPORT RTF
        COMPONENT runtime
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include/sharedlib++)

set_property(GLOBAL APPEND PROPERTY RTF_LIBS RTF_sharedlib++)
set_property(TARGET RTF_sharedlib++ PROPERTY INCLUDE_DIRS ${RTF_TREE_INCLUDE_DIRS})

