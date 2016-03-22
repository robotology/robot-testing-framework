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
#include <rtf/ConsoleListener.h>
#include <rtf/TestAssert.h>

using namespace RTF;

class MyTest : public TestCase {
public:
    MyTest() : TestCase("MyTest") {

    }

    virtual ~MyTest() { }

    virtual bool setup(int argc, char** argv) {
        RTF_TEST_REPORT("running MyTest::setup...");
        return true;
    }

    virtual void tearDown() {
        RTF_TEST_REPORT("running MyTest::teardown...");
        RTF_ASSERT_ERROR("this is just for example!");
    }

    virtual void run() {

        RTF_TEST_REPORT("testing integers");
        RTF_TEST_FAIL_IF(2<3, "is not smaller");
        RTF_TEST_FAIL_IF(5<3, "is not smaller");
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

    // create a test runner
    TestRunner runner;
    MyTest atest;
    runner.addTest(&atest);
    runner.run(result);

    // return the number of failed tests
    return collector.failedCount();

}
