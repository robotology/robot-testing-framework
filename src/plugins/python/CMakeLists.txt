#  Sharedlib++
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

cmake_minimum_required(VERSION 2.8.9)

project(RTF_python)


# option (RTF_USE_PYTHON_VERSION "" CACHE STRING "Specify python version to use")
set(RTF_USE_PYTHON_VERSION "2" CACHE STRING "Specify python version to use (only Python 2 is supported at the moment)" )

#find_package(PythonInterp ${YARP_USE_PYTHON_VERSION} REQUIRED)
if(RTF_USE_PYTHON_VERSION)
    find_package(PythonInterp ${RTF_USE_PYTHON_VERSION} REQUIRED)
    find_package(PythonLibs ${RTF_USE_PYTHON_VERSION} EXACT REQUIRED)
else()
    find_package(PythonInterp REQUIRED)
    find_package(PythonLibs REQUIRED)
endif()

set_property(GLOBAL APPEND PROPERTY RTF_INTERNAL_DEFS " -DENABLE_PYTHON_PLUGIN")
set_property(GLOBAL APPEND PROPERTY RTF_TREE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
get_property(RTF_TREE_INCLUDE_DIRS GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)

get_property(RTF_LIBS GLOBAL PROPERTY RTF_LIBS)
get_property(RTF_INTERNAL_INCLUDE_DIRS GLOBAL PROPERTY RTF_INTERNAL_INCLUDE_DIRS)
get_property(RTF_INTERNAL_LIBS GLOBAL PROPERTY RTF_INTERNAL_LIBS)

# Create the library
file(GLOB folder_source ./src/*.cpp)
file(GLOB_RECURSE folder_header ./include/rtf/python/*.h ./include/rtf/python/impl/*.h)
source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})

include_directories(${RTF_TREE_INCLUDE_DIRS}
                    ${RTF_INTERNAL_INCLUDE_DIRS}
                    ./include/rtf/python/impl
                    ${PYTHON_INCLUDE_DIR})
if(WIN32)
    add_library(RTF_python STATIC ${folder_source} ${folder_header} )
else()
    add_library(RTF_python SHARED ${folder_source} ${folder_header} )
endif()

link_libraries(${PYTHON_LIBRARY})
target_link_libraries(RTF_python ${PYTHON_LIBRARY})

# choose which header files should be installed
file(GLOB RTF_DLL_HEADERS ${PROJECT_SOURCE_DIR}/include/rtf/python/*.h)
set_property(TARGET RTF_python PROPERTY PUBLIC_HEADER ${RTF_DLL_HEADERS})

install(TARGETS RTF_python
        EXPORT RTF
        COMPONENT runtime
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include/rtf/python)

set_property(GLOBAL APPEND PROPERTY RTF_LIBS RTF_python)
set_property(TARGET RTF_python PROPERTY INCLUDE_DIRS ${RTF_TREE_INCLUDE_DIRS})


