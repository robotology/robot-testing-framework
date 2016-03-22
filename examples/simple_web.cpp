// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <rtf/TestCase.h>
#include <rtf/TestResult.h>
#include <rtf/TestResultCollector.h>
#include <rtf/TestRunner.h>
#include <rtf/TestSuit.h>
#include <rtf/WebProgressListener.h>
#include <rtf/TestAssert.h>

#ifdef _WIN32
	#include <Windows.h>
#else
    #include <unistd.h>
#endif

using namespace RTF;

class MyTest1 : public TestCase {
public:
    MyTest1() : TestCase("MyTest1") { }

    virtual void run() {
		srand(time(NULL));
        for (int i=0; i< 10; i++) {
			int a = rand() % 10;
			int b = rand() % 10;
            RTF_TEST_REPORT("testing smaller...");
            RTF_TEST_FAIL_IF(a<b, "is not smaller");
#ifdef _WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
        }
    }
};

class MyTest2 : public TestCase {
public:
    MyTest2() : TestCase("MyTest2") { }

    virtual void run() {
		srand(time(NULL));
        for (int i=0; i< 10; i++) {
			int a = rand() % 10;
			int b = rand() % 10;
            RTF_TEST_REPORT("testing equality...");
            RTF_TEST_FAIL_IF(a==b, "are not equal");
#ifdef _WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
		}
    }
};


int main(int argc, char** argv)
{
    // create a test listener to collect the result
    WebProgressListener web(8080, false);

    // create a collector to get computer readable
    // test results
    TestResultCollector collector;

    // create a test result sand add the listeners
    TestResult result;
    result.addListener(&web);
    result.addListener(&collector);
    printf("To see the test result, open a web browser and type 'http://127.0.0.1:8080'...\n");

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

    // return the number of failed tests
    return collector.failedCount();
}
