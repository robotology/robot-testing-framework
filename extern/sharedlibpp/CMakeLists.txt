#  Sharedlib++
#  Copyright: (C) 2015 Ali Paikan
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
target_link_libraries(RTF_sharedlib++)

# choose which header files should be installed 
set_property(TARGET RTF_sharedlib++ PROPERTY PUBLIC_HEADER ${RTF_TREE_INCLUDE_DIRS})

#install(TARGETS RTF_sharedlib++
#        EXPORT RTF_sharedlib++
#        COMPONENT runtime
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set_property(GLOBAL APPEND PROPERTY RTF_LIBS RTF_sharedlib++)
IF(NOT WIN32)
    set_property(GLOBAL APPEND PROPERTY RTF_LIBS dl)
ENDIF()
set_property(TARGET RTF_sharedlib++ PROPERTY INCLUDE_DIRS ${RTF_TREE_INCLUDE_DIRS})

