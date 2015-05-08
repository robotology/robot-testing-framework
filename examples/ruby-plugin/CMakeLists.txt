#  RTF
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


cmake_minimum_required(VERSION 2.8.9)

find_package(RTF)

include_directories(${CMAKE_SOURCE_DIR}
                    ${RTF_INCLUDE_DIRS})

add_executable(simple_run run.cpp)
target_link_libraries(simple_run ${RTF_LIBRARIES})

