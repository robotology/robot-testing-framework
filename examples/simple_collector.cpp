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
#include <rtf/TestRunner.h>
#include <rtf/TestSuit.h>
#include <rtf/ConsoleListener.h>
#include <rtf/TestAssert.h>
#include <rtf/TestResultCollector.h>
#include <rtf/TextOutputter.h>

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
        RTF_TEST_FAIL_IF(5==3, "are not equal");
    }
};


int main(int argc, char** argv)
{
    // create a test listener to print out the result
    ConsoleListener listener(false);

    // create a test result collector to collect the result
    TestResultCollector collector;

    // create a test result and add the listeners
    TestResult result;
    result.addListener(&listener);
    result.addListener(&collector);


    // create a test suite and the test cases
    TestSuit suit("MyTestSuit");
    MyTest1 test1;
    MyTest2 test2;
    suit.addTest(&test1);
    suit.addTest(&test2);

    // create a test runner
    TestRunner runner;
    runner.addTest(&suit);
    runner.run(result);

    // print out some simple statistics
    printf("\n-------- results ---------\n");
    printf("Total number of tests : %d\n", collector.testCount());
    printf("Number of passed tests: %d\n", collector.passedCount());
    printf("Number of failed tests: %d\n", collector.failedCount());

    // store the results in a text file
    TextOutputter outputter(collector);
    outputter.write("./result.txt");

    // return the number of failed tests
    return collector.failedCount();

}
