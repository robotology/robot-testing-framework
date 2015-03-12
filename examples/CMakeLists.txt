#  RTF
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# cmake_minimum_required(VERSION 2.6)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}
                    ../include)

LINK_LIBRARIES(RTF)  

ADD_EXECUTABLE(simple simple.cpp)
ADD_EXECUTABLE(simple_runner simple_runner.cpp)
ADD_EXECUTABLE(simple_suit simple_suit.cpp)
ADD_EXECUTABLE(simple_collector simple_collector.cpp)
ADD_EXECUTABLE(simple_fixture simple_fixture.cpp)

if(ENABLE_PLUGIN)
    add_subdirectory(plugin)
endif(ENABLE_PLUGIN)

