#!/usr/bin/ruby

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

# robottestingframework module is automatically imported by the ruby plugin loader
# to invoke the corresponding test case methods. To develop a new
# test case simply implement the following class; (setup and tearDown
# methods are optional) :
#
# class TestCase
#     def setup(param)
#         ...
#         return true
#     end
#
#     def run ... end
#
#     def tearDown ... end
# end
#
# The following methods are for reporting, failure or assertions:
#
# RobotTestingFramework::setName(name)             : sets the test name (defualt is the test filename)
# RobotTestingFramework::testReport(msg)           : reports a informative message
# RobotTestingFramework::testCheck(condition, msg) : reports the test message and marks the test as failed if condition is false
# RobotTestingFramework::assertError(msg)          : throws an error exception with message
# RobotTestingFramework::asserFail(msg)            : throws a failure exception with message
#

class TestCase
    # setup is called before the test's run to setup
    # the user defined fixture
    # @return Boolean (True/False uppon success or failure)
    def setup(param)
        RobotTestingFramework::testReport("Preparing setup...")
        return true
    end

    # The implementation of the test goes here
    def run
        RobotTestingFramework::testCheck(5>3, "5 is bigger than 3.")
        RobotTestingFramework::testCheck(5<3, "5 is smaller than 3.")
    end

    # tearDown is called after the test's run to tear down
    # the user defined fixture
    def tearDown
        RobotTestingFramework::testReport("Tearing down...")
    end
end

