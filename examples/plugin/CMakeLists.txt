#  RTF
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# cmake_minimum_required(VERSION 2.6)

get_property(RTF_INCLUDE_DIRS GLOBAL PROPERTY RTF_INCLUDE_DIRS)
get_property(RTF_LIBRARIES GLOBAL PROPERTY RTF_LIBRARIES)


INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}
                    ${RTF_INCLUDE_DIRS})

ADD_LIBRARY(mytest SHARED MyTest.cpp MyTest.h)

LINK_LIBRARIES(RTF ${RTF_LIBRARIES})
ADD_EXECUTABLE(run run.cpp)

