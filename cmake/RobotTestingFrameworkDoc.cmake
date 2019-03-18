# Robot Testing Framework
#
# Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA


find_package(Doxygen)

if(DOXYGEN_FOUND)
  set(DOX_GENERATE_HTML YES)
  set(DOX_GENERATE_XML NO)
  set(DOX_GENERATE_TAGFILE "")
  option(RobotTestingFramework_DOXYGEN_XML "Generate doxygen XML output, for use by SWIG" NO)
  option(RobotTestingFramework_DOXYGEN_TAGFILE "Generate doxygen tag file, see http://www.doxygen.nl/manual/external.html" NO)
  mark_as_advanced(RobotTestingFramework_DOXYGEN_XML RobotTestingFramework_DOXYGEN_TAGFILE)
  if(RobotTestingFramework_DOXYGEN_XML)
      set(DOX_GENERATE_XML YES)
  endif()
  if(RobotTestingFramework_DOXYGEN_TAGFILE)
      set(DOX_GENERATE_TAGFILE "${CMAKE_BINARY_DIR}/dox/RobotTestingFramework.tag")
  endif()

  set(DOX_FILE Doxyfile.part)
  # RobotTestingFramework documentation is always verbose now.  It used to be
  # partially stripped of stuff less interesting to end-users.
  set(DOX_PATTERNS "*.h *.dox *.cpp")
  set(DOX_GENERATE_MAN NO)
  configure_file(${CMAKE_CURRENT_LIST_DIR}/doxygen/${DOX_FILE}.template
                 ${CMAKE_BINARY_DIR}/dox/${DOX_FILE})
  add_custom_target(dox COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/dox/${DOX_FILE})

  set(DOX_GENERATE_HTML NO)
  set(DOX_GENERATE_MAN YES)
  set(DOX_GENERATE_XML NO)
  set(DOX_GENERATE_TAGFILE "")
  set(DOX_PATTERNS "cmd_*.dox")
  configure_file(${CMAKE_CURRENT_LIST_DIR}/doxygen/${DOX_FILE}.template
                 ${CMAKE_BINARY_DIR}/dox/${DOX_FILE}.man)
  add_custom_target(man COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/dox/${DOX_FILE}.man)
endif(DOXYGEN_FOUND)
