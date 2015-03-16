#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

project(RTF)

set_property(GLOBAL APPEND PROPERTY RTF_TREE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
get_property(RTF_TREE_INCLUDE_DIRS GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)

# Create the library 
file(GLOB folder_source src/*.cpp)
file(GLOB_RECURSE folder_header ./include/*.h)
source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})

include_directories(${RTF_TREE_INCLUDE_DIRS})
add_library(RTF SHARED ${folder_source} ${folder_header})
target_link_libraries(RTF)

# choose which header files should be installed 
file(GLOB RTF_HEADERS ./include/*.h)
set_property(TARGET RTF PROPERTY PUBLIC_HEADER ${RTF_HEADERS})

install(TARGETS RTF
        EXPORT RTF
        COMPONENT runtime
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

set_property(GLOBAL APPEND PROPERTY RTF_LIBS RTF)
set_property(TARGET RTF PROPERTY INCLUDE_DIRS ${RTF_TREE_INCLUDE_DIRS})

