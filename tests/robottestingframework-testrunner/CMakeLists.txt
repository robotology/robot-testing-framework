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


# adding robottestingframework-testrunner tests
add_test(NAME TestRunnerLoadSimpleSuite
         COMMAND $<TARGET_FILE:RTF_testrunner> -v --no-output --suite ${CMAKE_CURRENT_SOURCE_DIR}/testsuite.xml
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_test(NAME TestRunnerLoadLegacySuit
         COMMAND $<TARGET_FILE:RTF_testrunner> -v --no-output --suit ${CMAKE_CURRENT_SOURCE_DIR}/testsuit.xml
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
