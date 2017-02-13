// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <stdlib.h>
#include <string>
#include <rtf/TestAssert.h>
#include <rtf/dll/Plugin.h>

#include <rtf/TestResultCollector.h>
#include <rtf/TestRunner.h>
#include <rtf/TestSuit.h>
#include <rtf/dll/DllFixturePluginLoader.h>

using namespace RTF;
using namespace RTF::plugin;

class MyTest1 : public TestCase {
public:
    MyTest1() : TestCase("MyTest1") { }

    virtual void run() {
        RTF_TEST_CHECK(3<5, "smaller");
    }
};

class MyTestSuit : public TestSuit {
public:
	MyTestSuit() : TestSuit("MyTestSuit") { }

	virtual void fixtureCollapsed(RTF::TestMessage reason) {
		colapseReason = reason.getMessage();
	}
public: 
	std::string colapseReason;
};

class MyFixturePluginLoader : public RTF::TestCase {
	std::string fixtureFilename;

public:
	MyFixturePluginLoader() : TestCase("FixturePluginLoader") {}

	virtual bool setup(int argc, char**argv)  {
		RTF_TEST_REPORT(Asserter::format("argc %d", argc));
		RTF_ASSERT_ERROR_IF(argc >= 1, "missing fixture filename in the paramater");
		fixtureFilename = argv[1];
		RTF_TEST_REPORT(fixtureFilename);
		return true;
	}

    virtual void run() {
        TestResultCollector collector;

        // create a test result and add the listeners
        TestResult result;
        result.addListener(&collector);

        MyTest1 test1;

        // create a test suits
        MyTestSuit suit;

        // create a fixture manager from the plugin for the test suit
		RTF_TEST_REPORT(Asserter::format("Loading the fixture manager plugin (%s)", fixtureFilename.c_str()));
		DllFixturePluginLoader* loader = new DllFixturePluginLoader();
		FixtureManager* fixture = loader->open(fixtureFilename);
		RTF_ASSERT_FAIL_IF(fixture, loader->getLastError());

        suit.addFixtureManager(fixture);		
        suit.addTest(&test1);

		RTF_TEST_FAIL_IF(fixture->getDispatcher() == (RTF::FixtureEvents*)(&suit), "FixtureEvents dispatcher is not set");
		fixture->setParam("MY_FIXTURE_TEST_PARAM");

        // create a test runner
        TestRunner runner;
        runner.addTest(&suit);
        runner.run(result);
		
		RTF_TEST_CHECK(getenv("MY_FIXTURE_TEST_SETUP") != NULL &&
			std::string(getenv("MY_FIXTURE_TEST_SETUP")) == "OK",
			"Checking FixtureManager::setup()");

		RTF_TEST_CHECK(getenv("MY_FIXTURE_TEST_CHECK") != NULL &&
			std::string(getenv("MY_FIXTURE_TEST_CHECK")) == "OK",
			"Checking FixtureManager::check()");

		RTF_TEST_CHECK(suit.colapseReason == "COLAPSED", "FixtureManager::fixtureCollapsed()");

		RTF_TEST_CHECK(getenv("MY_FIXTURE_TEST_TEARDOWN") != NULL &&
			std::string(getenv("MY_FIXTURE_TEST_TEARDOWN")) == "OK",
			"Checking FixtureManager::tearDown()");

//		delete fixture;
//		delete loader;
//		RTF_TEST_CHECK(getenv("MY_FIXTURE_TEST_DELETE") != NULL &&
//			std::string(getenv("MY_FIXTURE_TEST_DELETE")) == "OK",
//			"Checking deleteing FixtureManager");

        //RTF_TEST_REPORT(Asserter::format("count: %d", collector.failedCount()));		
        RTF_TEST_CHECK(collector.suitCount() == 1, "Checking suit count");
        RTF_TEST_CHECK(collector.passedSuitCount() == 1, "Checking passed suit count");
        RTF_TEST_CHECK(collector.failedSuitCount() == 0, "Checking failed suit count");
        RTF_TEST_CHECK(collector.testCount() == 1, "Checking tests count");
        RTF_TEST_CHECK(collector.passedCount() == 1, "Checking passed test count");
        RTF_TEST_CHECK(collector.failedCount() == 0, "Checking failed test count");
		
    }
};

PREPARE_PLUGIN(MyFixturePluginLoader)
