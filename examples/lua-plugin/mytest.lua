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
-- TestCase.setName(...)        : sets the test name
-- TestCase.testReport(...)     : reports a informative message
-- TestCase.testFail(...)       : reports a failure message
-- TestCase.assertError(...)    : throws an error exception with message
-- TestCase.asserFail(...)      : throws a failure exception with message
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
    TestCase.testReport("Checking integers")
    if(5>3) then 
        TestCase.testFail("5 is not smaller than 3.")
    end    
end


--
-- tearDown is called after the test run to tear down
-- user defined fixture
--
TestCase.tearDown = function()
    TestCase.testReport("Tearing down...")
end

