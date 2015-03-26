--
-- Copyright (C) 2015 iCub Facility
-- Authors: Ali Paikan
-- CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
--
 
--
-- TestCase table is used by the lua plugin loader
-- to invoke the corresponding methods:
--
-- TestCase.setup = function(options) ... return true end
-- TestCase.run = function() ... end 
-- TestCase.tearDown = function() ... end 
--
-- The following methods are for reporting, failure or assertions: 
--
-- TestCase.setName(name)             : sets the test name
-- TestCase.testReport(msg)           : reports a informative message
-- TestCase.testCheck(condition, msg) : reports a failure message
-- TestCase.assertError(msg)          : throws an error exception with message
-- TestCase.asserFail(msg)            : throws a failure exception with message
--

--
-- setup is called before the test run to setup 
-- user defined fixture
-- @return Boolean (true/false uppon success or failure)
--
TestCase.setup = function(parameter)
    TestCase.setName("MyTest")
    TestCase.testReport("Preparing setup...")
    return true;
end

--
-- The implementation of the test goes here
-- @return Boolean
--
TestCase.run = function()
    TestCase.testReport("Checking bigger...")
    TestCase.testCheck(5>3, "5 is not bigger than 3.")
    TestCase.testReport("Checking smaller...")
    TestCase.testCheck(5<3, "5 is not smaller than 3.")
end


--
-- tearDown is called after the test run to tear down
-- user defined fixture
--
TestCase.tearDown = function()
    TestCase.testReport("Tearing down...")
end

