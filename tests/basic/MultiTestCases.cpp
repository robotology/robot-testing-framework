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

using namespace RTF;


class MyTest : public TestCase {
public:
    MyTest() : TestCase("MyTest") { }

    virtual void run() {
        RTF_TEST_CHECK(2<3, "two is less than three");
    }
};


class MyTest2 : public TestCase {
public:
    MyTest2() : TestCase("MyTest") { }

    virtual void run() {
        RTF_TEST_CHECK(2==3, "two is equal to three");
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

        // create a test runner
        TestRunner runner;
        MyTest test1;
        MyTest2 test2;
        runner.addTest(&test1);
        runner.addTest(&test2);
        runner.run(result);

        //RTF_TEST_REPORT(Asserter::format("count: %d", collector.failedCount()));
        RTF_TEST_CHECK(collector.testCount() == 2, "Checking tests count");
        RTF_TEST_CHECK(collector.passedCount() == 1, "Checking passed count");
        RTF_TEST_CHECK(collector.failedCount() == 1, "Checking failed count");
    }
};

PREPARE_PLUGIN(MultiTestCases)
