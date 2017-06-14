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

set(CMAKE_SHARED_MODULE_PREFIX "")

add_library(myfixture MODULE MyFixManager.cpp MyFixManager.h)
target_link_libraries(myfixture ${RTF_LIBRARIES})

add_executable(test test.cpp)
target_link_libraries(test ${RTF_LIBRARIES})

