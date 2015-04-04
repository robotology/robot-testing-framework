#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# cmake_minimum_required(VERSION 2.6)
set(PROJECTNAME testrunner)
project(${PROJECTNAME})


get_property(RTF_TREE_INCLUDE_DIRS GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)
get_property(RTF_LIBS GLOBAL PROPERTY RTF_LIBS)
get_property(RTF_INTERNAL_INCLUDE_DIRS GLOBAL PROPERTY RTF_INTERNAL_INCLUDE_DIRS)
get_property(RTF_INTERNAL_LIBS GLOBAL PROPERTY RTF_INTERNAL_LIBS)
get_property(RTF_INTERNAL_DEFS GLOBAL PROPERTY RTF_INTERNAL_DEFS)

add_definitions(${RTF_INTERNAL_DEFS})
if(ENABLE_WEB_LISTENER)
    add_definitions("-DENABLE_WEB_LISTENER")
endif()
include_directories(./include
                    ${RTF_TREE_INCLUDE_DIRS}
                    ${TinyXML_INCLUDE_DIRS}
                    ${RTF_INTERNAL_INCLUDE_DIRS})

file(GLOB folder_source ./src/*.cpp)
file(GLOB_RECURSE folder_header ./include/*.h)
source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})

add_executable(${PROJECTNAME} ${folder_source} ${folder_header})
target_link_libraries(${PROJECTNAME} ${RTF_LIBS} ${RTF_INTERNAL_LIBS} ${TinyXML_LIBRARIES})

install(TARGETS ${PROJECTNAME}
        EXPORT ${PROJECTNAME}
        RUNTIME DESTINATION bin)

