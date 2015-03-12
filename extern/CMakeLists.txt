#  RobotTestingFramework
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

# Build plugin manager
if (ENABLE_PLUGIN OR BUILD_TESTRUNNER)
    add_subdirectory(sharedlibpp)
endif()

# Build TinyXml if it is not available
if (BUILD_TESTRUNNER)
    find_package(TinyXML)
    if(NOT TinyXML_FOUND)
        add_subdirectory(tinyxml)
    endif()
    set_property(GLOBAL APPEND PROPERTY RTF_INTERNAL_INCLUDE_DIRS ${TinyXML_INCLUDE_DIRS})
    set_property(GLOBAL APPEND PROPERTY RTF_INTERNAL_DEFS ${TinyXML_DEFINITIONS})
    set_property(GLOBAL APPEND PROPERTY RTF_INTERNAL_LIBS ${TinyXML_LIBRARIES})
endif()

