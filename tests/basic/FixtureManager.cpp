/*
 * Robot Testing Framework
 *
 * Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include <robottestingframework/TestAssert.h>
#include <robottestingframework/TestResultCollector.h>
#include <robottestingframework/TestRunner.h>
#include <robottestingframework/TestSuite.h>
#include <robottestingframework/dll/Plugin.h>

using namespace robottestingframework;


class MyTest1 : public TestCase
{
public:
    MyTest1() :
            TestCase("MyTest1")
    {
    }

    void run() override
    {
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(3 < 5, "smaller");
    }
};


class MyFixture : public FixtureManager
{
public:
    MyFixture(FixtureEvents* dispatcher) :
            FixtureManager(dispatcher)
    {
    }

    bool setup(int argc, char** argv) override
    {
        throw FixtureException(TestMessage("MyFixture cannot setup the fixture!"));
        return true;
    }

    bool check() override
    {
        return true;
    }

    void tearDown() override
    {
    }
};


class MyFixture2 : public FixtureManager
{
public:
    MyFixture2(FixtureEvents* dispatcher) :
            FixtureManager(dispatcher)
    {
    }

    bool setup(int argc, char** argv) override
    {
        return true;
    }

    bool check() override
    {
        return true;
    }

    void tearDown() override
    {
    }
};


class MyFixtureManager : public TestCase
{
public:
    MyFixtureManager() :
            TestCase("FixtureManager")
    {
    }

    void run() override
    {
        TestResultCollector collector;

        // create a test result and add the listeners
        TestResult result;
        result.addListener(&collector);

        MyTest1 test1;

        // create a test suites
        TestSuite suite("MyTestSuite");
        // create a fixture manager for the test suit
        MyFixture fixture(&suite);
        suite.addFixtureManager(&fixture);
        suite.addTest(&test1);

        TestSuite suite2("MyTestSuite");
        // create a fixture manager for the test suit
        MyFixture2 fixture2(&suite);
        suite2.addFixtureManager(&fixture2);
        suite2.addTest(&test1);

        // create a test runner
        TestRunner runner;
        runner.addTest(&suite);
        runner.addTest(&suite2);
        runner.run(result);

        //ROBOTTESTINGFRAMEWORK_TEST_REPORT(Asserter::format("count: %d", collector.failedCount()));
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.suiteCount() == 2, "Checking suite count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.passedSuiteCount() == 1, "Checking passed suite count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.failedSuiteCount() == 1, "Checking failed suite count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.testCount() == 1, "Checking tests count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.passedCount() == 1, "Checking passed test count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.failedCount() == 0, "Checking failed test count");
    }
};

ROBOTTESTINGFRAMEWORK_PREPARE_PLUGIN(MyFixtureManager)
