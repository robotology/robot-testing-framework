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
#include <ConsoleListener.h>
#include <TestRunner.h>

#include <SharedLibrary.h>
#include <SharedLibraryClass.h>

#include <tinyxml.h>

using namespace RTF;

int main(int argc, char *argv[]) {

	if(argc < 2) {
        printf("Usage: %s <plugin file name>\n", argv[0]);
        printf("for example: %s libmytest.so\n", argv[0]);
		return 0;
	}

    // load the test case plugin
    printf("Loading the plugin... \n");
    shlibpp::SharedLibraryClassFactory<TestCase> factory(argv[1]);
    if (!factory.isValid()) {
        printf("error (%s) : %s\n", shlibpp::Vocab::decode(factory.getStatus()).c_str(),
                                    factory.getLastNativeError().c_str());
        return 0;
	}

    // create an instance of the test case from the plugin
    shlibpp::SharedLibraryClass<TestCase> atest(factory);

    // create a test listener to collect the result
    ConsoleListener listener(false);

    // create a test result and add the listeners
    TestResult result;
    result.addListener(&listener);

    // create a test runner and run the test case
    TestRunner runner;
    runner.addTest(&atest.getContent());
    runner.run(result);

    return 0;
}
