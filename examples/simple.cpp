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
#include <TestAssert.h>

using namespace RTF;

class MyTest : public TestCase {
public:
    MyTest() : TestCase("MyTest") {

    }

    virtual ~MyTest() { }

    virtual bool setup(int argc, char **argv) {
        RTF_TEST_REPORT("running MyTest::setup...");
        return true;
    }

    virtual void tearDown() {
        RTF_TEST_REPORT("running MyTest::teardown...");
        RTF_ASSERT_ERROR("this is just for example!");
    }

    virtual void run() {

        RTF_TEST_REPORT("testing integers");
        RTF_TEST_CHECK(2<3, "is not smaller");
        int a = 5;
        int b = 3;
        RTF_TEST_CHECK(a<b, Asserter::format("%d is not smaller than %d.", a, b));
    }

};

int main(int argc, char** argv)
{
    // create a test listener to collect the result
    // and enbale the verbose mode
    ConsoleListener listener(true);

    // create a test result and add the listeners
    TestResult result;
    result.addListener(&listener);

    // calling a test case
    MyTest atest;
    atest.TestCase::run(result);

    return 0;

}
