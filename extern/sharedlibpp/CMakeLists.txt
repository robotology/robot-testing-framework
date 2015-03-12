#  Sharedlib++
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

cmake_minimum_required(VERSION 2.6)

set(PROJECTNAME RTF_sharedlib++)
project(${PROJECTNAME})


# Create the library 
file(GLOB folder_source ./src/*.cpp)
file(GLOB_RECURSE folder_header ./include/*.h)
source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})

include_directories(./include)
add_library(${PROJECTNAME} STATIC ${folder_source} ${folder_header} )
target_link_libraries(${PROJECTNAME})

set(SharedLibPP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SharedLibPP_LIBRARIES "${PROJECTNAME}") #PARENT_SCOPE 

set_property(GLOBAL APPEND PROPERTY RTF_INCLUDE_DIRS ${SharedLibPP_INCLUDE_DIRS})

set_property(GLOBAL APPEND PROPERTY RTF_LIBRARIES ${SharedLibPP_LIBRARIES})
IF(NOT WIN32)
    set_property(GLOBAL APPEND PROPERTY RTF_LIBRARIES dl)
ENDIF()


#install(TARGETS ComanSimUtils EXPORT RTF COMPONENT runtime DESTINATION lib${LIB_SUFFIX})
#set_property(TARGET ComanSimUtils PROPERTY INCLUDE_DIRS ${COMAMSIM_INCLUDE_DIRS})
#install(DIRECTORY ${PROJECT_SOURCE_DIR}/ COMPONENT development DESTINATION include/comansim FILES_MATCHING PATTERN "*.h" PATTERN ".*" EXCLUDE)

#install(TARGETS ${PROJECTNAME}
#        EXPORT RTF
#        COMPONENT runtime
#        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
#        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
#        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")

#set_property(GLOBAL APPEND PROPERTY RTF_LIBS ${PROJECTNAME})

