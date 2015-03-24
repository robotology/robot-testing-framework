// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <stdio.h>
#include <TestCase.h>
#include <TestResult.h>
#include <TestRunner.h>
#include <TestSuit.h>
#include <FixtureManager.h>
#include <ConsoleListener.h>
#include <TestAssert.h>

using namespace RTF;

class MyTest1 : public TestCase {
public:
    MyTest1() : TestCase("MyTest1") { }

    virtual void run() {
        RTF_TEST_REPORT("testing smaller");
        RTF_TEST_CHECK(3<5, "is not smaller");
    }
};

class MyTest2 : public TestCase {
public:
    MyTest2() : TestCase("MyTest2") { }

    virtual void run() {
        RTF_TEST_REPORT("testing equality");
        RTF_TEST_CHECK(3==3, "are not equal");
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

    // create a test result and add the listeners
    TestResult result;
    result.addListener(&listener);

    // create a test suit
    TestSuit suit("MyTestSuit");

    // create a fixture manager for the test suit
    MyFixture fixture(&suit);
    suit.setFixtureManager(&fixture);

    // creates test cases and add them to the suit
    MyTest1 test1;
    MyTest2 test2;
    suit.addTest(&test1);
    suit.addTest(&test2);

    // create a test runner and run the tests
    TestRunner runner;    
    runner.addTest(&suit);
    runner.run(result);

    return 0;
}
