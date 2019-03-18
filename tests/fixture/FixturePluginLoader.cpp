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
#include <robottestingframework/dll/DllFixturePluginLoader.h>
#include <robottestingframework/dll/Plugin.h>

#include <cstdlib>
#include <string>

using namespace robottestingframework;
using namespace robottestingframework::plugin;

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

class MyTestSuite : public TestSuite
{
public:
    MyTestSuite() :
            TestSuite("MyTestSuite")
    {
    }

    void fixtureCollapsed(TestMessage reason) override
    {
        colapseReason = reason.getMessage();
    }

public:
    std::string colapseReason;
};

class MyFixturePluginLoader : public TestCase
{
    std::string fixtureFilename;

public:
    MyFixturePluginLoader() :
            TestCase("FixturePluginLoader")
    {
    }

    bool setup(int argc, char** argv) override
    {
        ROBOTTESTINGFRAMEWORK_TEST_REPORT(Asserter::format("argc %d", argc));
        ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(argc >= 1, "missing fixture filename in the paramater");
        fixtureFilename = argv[1];
        ROBOTTESTINGFRAMEWORK_TEST_REPORT(fixtureFilename);
        return true;
    }

    void run() override
    {
        TestResultCollector collector;

        // create a test result and add the listeners
        TestResult result;
        result.addListener(&collector);

        MyTest1 test1;

        // create a test suites
        MyTestSuite suite;

        // create a fixture manager from the plugin for the test suite
        ROBOTTESTINGFRAMEWORK_TEST_REPORT(Asserter::format("Loading the fixture manager plugin (%s)", fixtureFilename.c_str()));
        auto* loader = new DllFixturePluginLoader();
        FixtureManager* fixture = loader->open(fixtureFilename);
        ROBOTTESTINGFRAMEWORK_ASSERT_FAIL_IF_FALSE(fixture, loader->getLastError());

        suite.addFixtureManager(fixture);
        suite.addTest(&test1);

        ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE(fixture->getDispatcher() == (FixtureEvents*)(&suite), "FixtureEvents dispatcher is not set");
        fixture->setParam("MY_FIXTURE_TEST_PARAM");

        // create a test runner
        TestRunner runner;
        runner.addTest(&suite);
        runner.run(result);

        ROBOTTESTINGFRAMEWORK_TEST_CHECK(getenv("MY_FIXTURE_TEST_SETUP") != nullptr && std::string(getenv("MY_FIXTURE_TEST_SETUP")) == "OK",
                                         "Checking FixtureManager::setup()");

        ROBOTTESTINGFRAMEWORK_TEST_CHECK(getenv("MY_FIXTURE_TEST_CHECK") != nullptr && std::string(getenv("MY_FIXTURE_TEST_CHECK")) == "OK",
                                         "Checking FixtureManager::check()");

        ROBOTTESTINGFRAMEWORK_TEST_CHECK(suite.colapseReason == "COLAPSED", "FixtureManager::fixtureCollapsed()");

        ROBOTTESTINGFRAMEWORK_TEST_CHECK(getenv("MY_FIXTURE_TEST_TEARDOWN") != nullptr && std::string(getenv("MY_FIXTURE_TEST_TEARDOWN")) == "OK",
                                         "Checking FixtureManager::tearDown()");

        //        delete fixture;
        //        delete loader;
        //        ROBOTTESTINGFRAMEWORK_TEST_CHECK(getenv("MY_FIXTURE_TEST_DELETE") != nullptr &&
        //            std::string(getenv("MY_FIXTURE_TEST_DELETE")) == "OK",
        //            "Checking deleteing FixtureManager");

        //ROBOTTESTINGFRAMEWORK_TEST_REPORT(Asserter::format("count: %d", collector.failedCount()));
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.suiteCount() == 1, "Checking suite count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.passedSuiteCount() == 1, "Checking passed suite count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.failedSuiteCount() == 0, "Checking failed suite count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.testCount() == 1, "Checking tests count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.passedCount() == 1, "Checking passed test count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.failedCount() == 0, "Checking failed test count");
    }
};

ROBOTTESTINGFRAMEWORK_PREPARE_PLUGIN(MyFixturePluginLoader)
