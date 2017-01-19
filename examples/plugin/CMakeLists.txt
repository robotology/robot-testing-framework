#  RTF
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


cmake_minimum_required(VERSION 3.0)

find_package(RTF)
find_package(RTF COMPONENTS DLL)

include_directories(${CMAKE_SOURCE_DIR}
                    ${RTF_INCLUDE_DIRS})

add_library(mytest MODULE MyTest.cpp MyTest.h)
target_link_libraries(mytest ${RTF_LIBRARIES})

add_executable(simple_run run.cpp)
target_link_libraries(simple_run ${RTF_LIBRARIES})

