# Copyright: (C) 2009 RobotCub Consortium
# Author: Paul Fitzpatrick
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

# This file is the official location of the current RTF version number.


## manually increase tweak number when required. Set to zero when
# bumping VERSION_PATCH
set(RTF_VERSION_MAJOR "1")
set(RTF_VERSION_MINOR "3")
set(RTF_VERSION_PATCH "4")
set(RTF_VERSION_TWEAK "")
set(RTF_VERSION_STRING "")

#set(RTF_VERSION_ABI "1")

# Generate RTF_VERSION
if(RTF_VERSION_TWEAK)
    set(RTF_VERSION "${RTF_VERSION_MAJOR}.${RTF_VERSION_MINOR}.${RTF_VERSION_PATCH}.${RTF_VERSION_TWEAK}")
else()
    set(RTF_VERSION "${RTF_VERSION_MAJOR}.${RTF_VERSION_MINOR}.${RTF_VERSION_PATCH}")
endif()

# Generate RTF_VERSION_STRING if not set
set(RTF_VERSION_STRING "${RTF_VERSION}")
if(NOT RTF_VERSION_STRING)
    set(RTF_VERSION_STRING "${RTF_VERSION}")
endif()

#set(RTF_GENERIC_SOVERSION "${RTF_VERSION_ABI}")
