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


# build tests
include(RobotTestingFrameworkTestHelpers)

if (BUILD_TESTING)
  # enable Robot Testing Framework testing
  enable_robottestingframework_tests()

  # adding api c++ tests
  add_subdirectory(api)

  if (BUILD_TESTRUNNER)
    # adding basic tests
    add_subdirectory(basic)

    # adding basic tests
    add_subdirectory(fixture)

    # adding lua tests
    add_subdirectory(lua)

    # adding python tests
    add_subdirectory(python)

    # adding python tests
    add_subdirectory(ruby)

    # adding robottestingframework-testrunner tests
    add_subdirectory(robottestingframework-testrunner)

    # adding robottestingframework_add_suite tests
    add_subdirectory(robottestingframework_add_suite)
  endif()
endif()
