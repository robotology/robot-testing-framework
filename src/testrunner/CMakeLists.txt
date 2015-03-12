#  RTF
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# cmake_minimum_required(VERSION 2.6)
set(PROJECTNAME testrunner)
project(${PROJECTNAME})



get_property(RTF_INCLUDE_DIRS GLOBAL PROPERTY RTF_INCLUDE_DIRS)
get_property(RTF_LIBRARIES GLOBAL PROPERTY RTF_LIBRARIES)

file(GLOB folder_source *.cpp)
file(GLOB_RECURSE folder_header *.h)
source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})


INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}
                    ../../include
                    ${RTF_INCLUDE_DIRS}
                    ${TinyXML_INCLUDE_DIRS})

add_executable(${PROJECTNAME} ${folder_source} ${folder_header})
target_link_libraries(${PROJECTNAME} RTF ${RTF_LIBRARIES} ${TinyXML_LIBRARIES})

