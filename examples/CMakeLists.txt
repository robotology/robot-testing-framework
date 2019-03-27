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

# Build examples
if (BUILD_EXAMPLES)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/examples")

  add_executable(robottestingframework_simple simple.cpp)
  target_link_libraries(robottestingframework_simple RobotTestingFramework::RTF)

  add_executable(robottestingframework_simple_suite simple_suite.cpp)
  target_link_libraries(robottestingframework_simple_suite RobotTestingFramework::RTF)

  add_executable(robottestingframework_simple_collector simple_collector.cpp)
  target_link_libraries(robottestingframework_simple_collector RobotTestingFramework::RTF)

  add_executable(robottestingframework_simple_runner simple_runner.cpp)
  target_link_libraries(robottestingframework_simple_runner RobotTestingFramework::RTF)

  add_executable(robottestingframework_simple_fixture simple_fixture.cpp)
  target_link_libraries(robottestingframework_simple_fixture RobotTestingFramework::RTF)

  if(ENABLE_WEB_LISTENER)
    add_executable(robottestingframework_simple_web simple_web.cpp)
    target_link_libraries(robottestingframework_simple_web RobotTestingFramework::RTF)
  endif()
endif()
