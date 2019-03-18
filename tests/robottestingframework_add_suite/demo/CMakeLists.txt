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


set(RobotTestingFramework_ADD_SUITE_DEBUG TRUE)
cmake_minimum_required(VERSION 3.5)
project(robottestingframework_add_suite_demo)
enable_testing()

find_package(RobotTestingFramework REQUIRED)

robottestingframework_add_plugin(demo_fixturemanager SOURCES demo_fixturemanager.cpp)
target_link_libraries(demo_fixturemanager RobotTestingFramework::RTF
                                          RobotTestingFramework::RTF_dll)

robottestingframework_add_plugin(demo_testcase SOURCES demo_testcase.cpp)
target_link_libraries(demo_testcase RobotTestingFramework::RTF
                                    RobotTestingFramework::RTF_dll)

robottestingframework_add_suite(NAME demo
                                RobotTestingFramework_FIXTURE demo_fixturemanager
                                RobotTestingFramework_TEST demo_testcase TYPE dll
                                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                                WEB_REPORTER
                                WEB_PORT 2020)
