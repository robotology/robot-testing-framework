-- Robot Testing Framework
--
-- Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
--
-- This library is free software; you can redistribute it and/or
-- modify it under the terms of the GNU Lesser General Public
-- License as published by the Free Software Foundation; either
-- version 2.1 of the License, or (at your option) any later version.
--
-- This library is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
-- Lesser General Public License for more details.
--
-- You should have received a copy of the GNU Lesser General Public
-- License along with this library; if not, write to the Free Software
-- Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

--
-- The TestCase table is used by the lua plugin loader
-- to invoke the corresponding methods:
--
-- TestCase.setup = function(options) ... return true end
-- TestCase.run = function() ... end
-- TestCase.tearDown = function() ... end
--
-- The following methods are for reporting, failures or assertions:
--
-- robottestingframework.setName(name)              : sets the test name (defualt is the test filename)
-- robottestingframework.testReport(msg)            : reports a informative message
-- robottestingframework.testCheck(condition, msg)  : reports the test message and marks the test as failed if condition is false
-- robottestingframework.testFailIf(condition, msg) : marks the test as failed and reports failure message (the reason) if condition is false
-- robottestingframework.assertError(msg)           : throws an error exception with message
-- robottestingframework.asserFail(msg)             : throws a failure exception with message
-- robottestingframework.getEnvironment()           : returns the test environment params
--

--
-- setup is called before the test's run to setup
-- the user defined fixture
-- @return Boolean (true/false uppon success or failure)
--
TestCase.setup = function(parameter)
    robottestingframework.setName("LuaTestCase")
    return true;
end

--
-- The implementation of the test goes here
--
TestCase.run = function()
    robottestingframework.testCheck(5>3, "Cheking robottestingframework.testCheck")
    robottestingframework.testReport("Cheking robottestingframework.testFailIf")
    robottestingframework.testFailIf(true, "testFailIf")
end


--
-- tearDown is called after the test's run to tear down
-- the user defined fixture
--
TestCase.tearDown = function()
end
