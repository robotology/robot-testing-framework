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
#include <WebProgressListener.h>
#include <TestAssert.h>

#include <unistd.h>

using namespace RTF;

class MyTest1 : public TestCase {
public:
    MyTest1() : TestCase("MyTest1") { }

    virtual void run() {
        for (int i=0; i< 20; i++) {
            RTF_TEST_REPORT("testing smaller");
            RTF_TEST_CHECK(3<5, "is not smaller");
            RTF_TEST_CHECK(3>5, "is not bigger");
            sleep(2);
        }
    }
};

class MyTest2 : public TestCase {
public:
    MyTest2() : TestCase("MyTest2") { }

    virtual void run() {
        RTF_TEST_REPORT("testing equality");
        RTF_TEST_CHECK(5==3, "are not equal");
    }
};


int main(int argc, char** argv)
{
    // create a test listener to collect the result
    WebProgressListener listener(8080, false);

    // create a test result and add the listeners
    TestResult result;
    result.addListener(&listener);

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

    return 0;

}