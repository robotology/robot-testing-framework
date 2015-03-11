#  RTF
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# cmake_minimum_required(VERSION 2.6)


INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}
                    ../../include
                    ../../extern/sharedlibpp/include)

ADD_LIBRARY(mytest SHARED MyTest.cpp MyTest.h)

IF(WIN32)
    LINK_LIBRARIES(rtf sharedlib++)
ELSE()
    LINK_LIBRARIES(rtf sharedlib++ dl)
ENDIF()

ADD_EXECUTABLE(run run.cpp)

