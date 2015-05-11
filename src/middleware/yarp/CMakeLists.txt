#  RTF
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

cmake_minimum_required(VERSION 2.8.9)


project(RTF_yarp)

find_package(YARP REQUIRED)

set_property(GLOBAL APPEND PROPERTY RTF_TREE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
get_property(RTF_TREE_INCLUDE_DIRS GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)

set(RTF_YARP_PUBLIC_HDRS include/rtf/yarp/YarpTestCase.h)

install(FILES ${RTF_YARP_PUBLIC_HDRS}
        DESTINATION include/rtf/yarp)

#add yarp fixture plugin
add_subdirectory(fixture-ymanager)

