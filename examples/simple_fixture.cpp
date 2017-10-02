// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <stdio.h>
#include <rtf/TestCase.h>
#include <rtf/TestResult.h>
#include <rtf/TestResultCollector.h>
#include <rtf/TestRunner.h>
#include <rtf/TestSuite.h>
#include <rtf/FixtureManager.h>
#include <rtf/ConsoleListener.h>
#include <rtf/TestAssert.h>

using namespace RTF;

class MyTest1 : public TestCase {
public:
    MyTest1() : TestCase("MyTest1") { }

    virtual void run() {
        RTF_TEST_REPORT("testing smaller");
        RTF_TEST_FAIL_IF(3<5, "is not smaller");
    }
};

class MyTest2 : public TestCase {
public:
    MyTest2() : TestCase("MyTest2") { }

    virtual void run() {
        RTF_TEST_REPORT("testing equality");
        RTF_TEST_FAIL_IF(3==3, "are not equal");
    }
};

class MyFixture : public FixtureManager {
public:
    MyFixture(RTF::FixtureEvents* dispatcher)
        : FixtureManager(dispatcher) { }

    bool setup(int argc, char**argv) {
        // setup and initialize the fixture
        // ...
        printf("Myfixture setup!\n");
        // return true if everything is fine.
        return true;
    }

    bool check() {
        printf("Myfixture checking ...\n");
        return true;
    }

    void tearDown() {
        // uninitialize the fixture
        // ...
        printf("Myfixture tear down!\n");
        // for an example if there is any error during tear down,
        // throw an exception.
        throw FixtureException(TestMessage("MyFixture cannot tear down!"));
    }

};

int main(int argc, char** argv)
{
    // create a test listener to collect the result
    ConsoleListener listener(false);

    // create a collector to get computer readable
    // test results
    TestResultCollector collector;

    // create a test result and add the listeners
    TestResult result;
    result.addListener(&listener);
    result.addListener(&collector);

    // create a test suite
    TestSuite suite("MyTestSuite");

    // create a fixture manager for the test suit
    MyFixture fixture(&suite);
    suite.addFixtureManager(&fixture);

    // creates test cases and add them to the suit
    MyTest1 test1;
    MyTest2 test2;
    suite.addTest(&test1);
    suite.addTest(&test2);

    // create a test runner and run the tests
    TestRunner runner;
    runner.addTest(&suite);
    runner.run(result);

    // return the number of failed tests
    return collector.failedCount();
}
