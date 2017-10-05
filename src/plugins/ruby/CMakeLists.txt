#  Sharedlib++
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

cmake_minimum_required(VERSION 3.0)

project(RTF_ruby)

find_package(Ruby REQUIRED)

set_property(GLOBAL APPEND PROPERTY RTF_INTERNAL_DEFS " -DENABLE_RUBY_PLUGIN")
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
                    ${RUBY_INCLUDE_DIR}
                    ${RUBY_CONFIG_INCLUDE_DIR})

add_library(RTF_ruby ${folder_source} ${folder_header} )
target_link_libraries(RTF_ruby ${RTF_LIBS} ${RUBY_LIBRARY})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_nullptr)

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                                  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)


# choose which header files should be installed
file(GLOB RTF_DLL_HEADERS ${PROJECT_SOURCE_DIR}/include/rtf/ruby/*.h)
set_property(TARGET RTF_ruby PROPERTY PUBLIC_HEADER ${RTF_DLL_HEADERS})

install(TARGETS RTF_ruby
        EXPORT RTF
        COMPONENT runtime
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include/rtf/ruby)

set_property(GLOBAL APPEND PROPERTY RTF_LIBS RTF_ruby)
set_property(TARGET RTF_ruby PROPERTY INCLUDE_DIRS ${RTF_TREE_INCLUDE_DIRS})

