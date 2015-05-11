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
#include <rtf/TestSuit.h>
#include <rtf/ConsoleListener.h>
#include <rtf/TestRunner.h>
#include <rtf/TestAssert.h>
#include <rtf/dll/DllFixturePluginLoader.h>


using namespace RTF;
using namespace RTF::plugin;

class MyTest1 : public TestCase {
public:
    MyTest1() : TestCase("MyTest1") { }

    virtual void run() {
        RTF_TEST_REPORT("testing smaller");
        RTF_TEST_CHECK(3<5, "is not smaller");
    }
};


int main(int argc, char *argv[]) {

	if(argc < 2) {
        printf("Usage: %s <fixcture manager plugin file name>\n", argv[0]);
        printf("for example: %s libmyfixture.so\n", argv[0]);
		return 0;
	}

    // load the test case plugin
    printf("Loading the fixture manager plugin... \n");
    DllFixturePluginLoader loader;
    FixtureManager* fixture = loader.open(argv[1]);
    if(fixture == NULL) {
        printf("%s\n", loader.getLastError().c_str());
        return 0;
	}

    // create a test listener to collect the result
    ConsoleListener listener(false);

    // create a test result and add the listeners
    TestResult result;
    result.addListener(&listener);

    // create a test suit
    TestSuit suit("MyTestSuit");

    // set the fixture manager for the test suit
    suit.setFixtureManager(fixture);

    // creates test cases and add them to the suit
    MyTest1 test1;
    suit.addTest(&test1);

    // create a test runner and run the tests
    TestRunner runner;
    runner.addTest(&suit);
    runner.run(result);

    return 0;
}
