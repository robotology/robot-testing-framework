#  RTF
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# cmake_minimum_required(VERSION 2.6)

get_property(RTF_TREE_INCLUDE_DIRS GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)
get_property(RTF_LIBS GLOBAL PROPERTY RTF_LIBS)


include_directories(${CMAKE_SOURCE_DIR}
                    ${RTF_TREE_INCLUDE_DIRS})

add_library(mytest SHARED MyTest.cpp MyTest.h)

add_executable(run run.cpp)
target_link_libraries(run ${RTF_LIBS})



