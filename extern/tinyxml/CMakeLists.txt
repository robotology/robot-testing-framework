# Copyright (C) 2012  iCub Facility, Istituto Italiano di Tecnologia
# Author: Ali Paikan <ali.paikan@iit.it>
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT


# TinyXML
set(PROJECTNAME RTF_tinyxml)
project(${PROJECTNAME})

set(tinyxml_SRCS
    src/tinyxml.cpp
    src/tinyxmlerror.cpp
    src/tinyxmlparser.cpp
)

set(tinyxml_HDRS
    src/tinystr.h
    src/tinyxml.h
)

add_definitions("-DTIXML_USE_STL")
add_library(${PROJECTNAME} STATIC ${tinyxml_SRCS})

set(TinyXML_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src PARENT_SCOPE)
set(TinyXML_LIBRARIES "${PROJECTNAME}" PARENT_SCOPE)
set(TinyXML_DEFINITIONS "-DTIXML_USE_STL " PARENT_SCOPE)

#set_property(GLOBAL APPEND PROPERTY RTF_INTERNAL_INCLUDE_DIRS ${TinyXML_INCLUDE_DIRS})
#set_property(GLOBAL APPEND PROPERTY RTF_INTERNAL_DEFS ${TinyXML_DEFINITIONS})
#set_property(GLOBAL APPEND PROPERTY RTF_INTERNAL_LIBS ${TinyXML_LIBRARIES})

