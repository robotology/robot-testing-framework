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


if (ENABLE_PLUGIN)
    # Build a ficture plugin
    set(CMAKE_SHARED_MODULE_PREFIX "")
    add_library(myfixture MODULE MyFixManager.cpp MyFixManager.h)
    target_link_libraries(myfixture RobotTestingFramework::RTF
                                    RobotTestingFramework::RTF_dll)

    # add the FixturePluginLoader test

    add_robottestingframework_cpptest(NAME FixturePluginLoader
                                      SRCS FixturePluginLoader.cpp
                                      PARAM "$<TARGET_FILE:myfixture>")
endif()
