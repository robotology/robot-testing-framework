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

class MyTest2 : public TestCase {
public:
    MyTest2() : TestCase("MyTest2") { }

    virtual void run() {
        RTF_TEST_CHECK(5==3, "equal");
    }
};

class MultiTestCases : public RTF::TestCase {
public:
    MultiTestCases() : TestCase("MultiTestCases") {}

    virtual void run() {
        TestResultCollector collector;

        // create a test result and add the listeners
        TestResult result;
        result.addListener(&collector);

        // create a test suit and the test cases
        TestSuit suit("MyTestSuit");
        MyTest1 test1;
        MyTest2 test2;
        suit.addTest(&test1);
        suit.addTest(&test2);

        // create a test runner
        TestRunner runner;
        runner.addTest(&suit);
        runner.run(result);

        //RTF_TEST_REPORT(Asserter::format("count: %d", collector.failedCount()));
        RTF_TEST_CHECK(collector.suitCount() == 1, "Checking suit count");
        RTF_TEST_CHECK(collector.passedSuitCount() == 0, "Checking passed suit count");
        RTF_TEST_CHECK(collector.failedSuitCount() == 1, "Checking failed suit count");
        RTF_TEST_CHECK(collector.testCount() == 2, "Checking tests count");
        RTF_TEST_CHECK(collector.passedCount() == 1, "Checking passed test count");
        RTF_TEST_CHECK(collector.failedCount() == 1, "Checking failed test count");
    }
};

PREPARE_PLUGIN(MultiTestCases)
