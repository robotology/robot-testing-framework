#  RobotTestingFramework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Daniele E. Domenichelli <daniele.domenichelli@iit.it>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

set(RTF_VERSION 1.0.0)


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was RTFConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set_and_check(RTF_INCLUDEDIR "/home/apaikan/Install/robotology/robot-testing/src/rtf/include")

if(NOT TARGET RTF::RTF)
  include("${CMAKE_CURRENT_LIST_DIR}/RTFTargets.cmake")
endif()

set(RTF_LIBRARIES RTF::RTF)
set(RTF_INCLUDE_DIRS "${RTF_INCLUDEDIR}")

if(TARGET RTF::RTF_dll)
  set(RTF_DLL_FOUND TRUE)
  set_and_check(RTF_DLL_INCLUDEDIR "/home/apaikan/Install/robotology/robot-testing/src/plugins/dll/include")
  list(APPEND RTF_LIBRARIES RTF::RTF_dll)
  list(APPEND RTF_INCLUDE_DIRS "${RTF_DLL_INCLUDEDIR}")
else()
  set(RTF_DLL_FOUND FALSE)
endif()

check_required_components(RTF)
