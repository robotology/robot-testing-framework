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


if(ENABLE_PLUGIN)
    # SingleTestCase
    add_robottestingframework_cpptest(NAME SingleTestCase SRCS SingleTestCase.cpp)

    # SingleTestCase
    add_robottestingframework_cpptest(NAME MultiTestCases SRCS MultiTestCases.cpp)

    # SingleTestSuite
    add_robottestingframework_cpptest(NAME SingleTestSuite SRCS SingleTestSuite.cpp)

    # SingleTestSuite
    add_robottestingframework_cpptest(NAME FixtureManager SRCS FixtureManager.cpp)

    if (UNIX)
        # WebProgListener
        add_robottestingframework_cpptest(NAME WebProgListener SRCS WebProgListener.cpp)
    endif (UNIX)
endif()

