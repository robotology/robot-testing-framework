# Copyright (C) 2015 iCub Facility
# Authors: Ali Paikan
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

# RTF module is automatically imported by the ruby plugin loader
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
# RTF::setName(name)             : sets the test name (defualt is the test filename)
# RTF::testReport(msg)           : reports a informative message
# RTF::testCheck(condition, msg) : reports a failure message
# RTF::assertError(msg)          : throws an error exception with message
# RTF::asserFail(msg)            : throws a failure exception with message
#

class TestCase
    # setup is called before the test's run to setup 
    # the user defined fixture
    # @return Boolean (True/False uppon success or failure)
    def setup(param)
        RTF::testReport("Preparing setup...")
        return true
    end

    # The implementation of the test goes here
    def run
        RTF::testReport("Checking bigger...")
        RTF::testCheck(5>3, "5 is not bigger than 3.")
        RTF::testReport("Checking smaller...")
        RTF::testCheck(5<3, "5 is not smaller than 3.")
    end

    # tearDown is called after the test's run to tear down
    # the user defined fixture
    def tearDown
        RTF::testReport("Tearing down...")
    end
end

