#  Sharedlib++
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

cmake_minimum_required(VERSION 2.8.9)

project(RTF_lua)

find_package(Lua51 REQUIRED)

set_property(GLOBAL APPEND PROPERTY RTF_INTERNAL_DEFS " -DENABLE_LUA_PLUGIN")
set_property(GLOBAL APPEND PROPERTY RTF_TREE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
get_property(RTF_TREE_INCLUDE_DIRS GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)

get_property(RTF_LIBS GLOBAL PROPERTY RTF_LIBS)
get_property(RTF_INTERNAL_INCLUDE_DIRS GLOBAL PROPERTY RTF_INTERNAL_INCLUDE_DIRS)
get_property(RTF_INTERNAL_LIBS GLOBAL PROPERTY RTF_INTERNAL_LIBS)

# Create the library 
file(GLOB folder_source ./src/*.cpp)
file(GLOB_RECURSE folder_header ./include/*.h ./include/impl/*.h)
source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})

include_directories(${RTF_TREE_INCLUDE_DIRS}
                    ${RTF_INTERNAL_INCLUDE_DIRS}
                    ./include/impl
                    ${LUA_INCLUDE_DIR})

add_library(RTF_lua STATIC ${folder_source} ${folder_header} )
target_link_libraries(RTF_lua ${LUA_LIBRARY})


# choose which header files should be installed 
file(GLOB RTF_DLL_HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)
set_property(TARGET RTF_lua PROPERTY PUBLIC_HEADER ${RTF_DLL_HEADERS})

install(TARGETS RTF_lua
        EXPORT RTF
        COMPONENT runtime
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include/lua)

set_property(GLOBAL APPEND PROPERTY RTF_LIBS RTF_lua)
set_property(TARGET RTF_lua PROPERTY INCLUDE_DIRS ${RTF_TREE_INCLUDE_DIRS})

