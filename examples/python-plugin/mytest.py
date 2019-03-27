#!/usr/bin/python

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

'''
 robottestingframework module is automatically imported by the python plugin loader
 to invoke the corresponding test case methods. To develop a new
 test case simply implement the following class; (setup and tearDown
 methods are optional) :

 class TestCase:
     def setup(self, param):
         return True

     def run(self):

     def tearDown(self):


 The following methods are for reporting, failure or assertions:

 robottestingframework.setName(name)             : sets the test name (defualt is the test filename)
 robottestingframework.testReport(msg)           : reports a informative message
 robottestingframework.testCheck(condition, msg) : reports the test message and marks the test as failed if condition is false
 robottestingframework.assertError(msg)          : throws an error exception with message
 robottestingframework.asserFail(msg)            : throws a failure exception with message
'''

class TestCase:
    # setup is called before the test's run to setup
    # the user defined fixture
    # @return Boolean (True/False uppon success or failure)
    def setup(self, param):
        robottestingframework.testReport("Preparing setup...")
        return True

    # The implementation of the test goes here
    def run(self):
        robottestingframework.testCheck(5>3, "5 is bigger than 3.")
        robottestingframework.testCheck(5<3, "5 is smaller than 3.")

    # tearDown is called after the test's run to tear down
    # the user defined fixture
    def tearDown(self):
        robottestingframework.testReport("Tearing down...")
