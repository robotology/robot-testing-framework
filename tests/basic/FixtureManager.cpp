// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <rtf/TestAssert.h>
#include <rtf/dll/Plugin.h>

#include <rtf/TestResultCollector.h>
#include <rtf/TestRunner.h>
#include <rtf/TestSuit.h>

using namespace RTF;


class MyTest1 : public TestCase {
public:
    MyTest1() : TestCase("MyTest1") { }

    virtual void run() {
        RTF_TEST_CHECK(3<5, "smaller");
    }
};


class MyFixture : public FixtureManager {
public:
    MyFixture(RTF::FixtureEvents* dispatcher)
        : FixtureManager(dispatcher) { }

    bool setup(int argc, char**argv) {
        throw FixtureException(TestMessage("MyFixture cannot setup the fixture!"));
        return true;
    }

    bool check() { return true; }

    void tearDown() { }

};


class MyFixture2 : public FixtureManager {
public:
    MyFixture2(RTF::FixtureEvents* dispatcher)
        : FixtureManager(dispatcher) { }

    bool setup(int argc, char**argv) {
        return true;
    }

    bool check() { return true; }

    void tearDown() { }

};


class MyFixtureManager : public RTF::TestCase {
public:
    MyFixtureManager() : TestCase("FixtureManager") {}

    virtual void run() {
        TestResultCollector collector;

        // create a test result and add the listeners
        TestResult result;
        result.addListener(&collector);

        MyTest1 test1;

        // create a test suits
        TestSuit suit("MyTestSuit");
        // create a fixture manager for the test suit
        MyFixture fixture(&suit);
        suit.addFixtureManager(&fixture);
        suit.addTest(&test1);

        TestSuit suit2("MyTestSuit");
        // create a fixture manager for the test suit
        MyFixture2 fixture2(&suit);
        suit2.addFixtureManager(&fixture2);
        suit2.addTest(&test1);

        // create a test runner
        TestRunner runner;
        runner.addTest(&suit);
        runner.addTest(&suit2);
        runner.run(result);

        //RTF_TEST_REPORT(Asserter::format("count: %d", collector.failedCount()));
        RTF_TEST_CHECK(collector.suitCount() == 2, "Checking suit count");
        RTF_TEST_CHECK(collector.passedSuitCount() == 1, "Checking passed suit count");
        RTF_TEST_CHECK(collector.failedSuitCount() == 1, "Checking failed suit count");
        RTF_TEST_CHECK(collector.testCount() == 1, "Checking tests count");
        RTF_TEST_CHECK(collector.passedCount() == 1, "Checking passed test count");
        RTF_TEST_CHECK(collector.failedCount() == 0, "Checking failed test count");
    }
};

PREPARE_PLUGIN(MyFixtureManager)
