// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <rtf/TestCase.h>
#include <rtf/TestResult.h>
#include <rtf/TestResultCollector.h>
#include <rtf/ConsoleListener.h>
#include <rtf/TestAssert.h>
#include <rtf/Exception.h>


using namespace RTF;

class MyTest : public TestCase {
public:
    MyTest() : TestCase("ExceptionTest") { }

    virtual void run() {

        RTF_TEST_REPORT("Cheking TestFailureException");
        try {
            throw RTF::TestFailureException(TestMessage("FAILURE"));
        }
        catch(RTF::TestFailureException& e) {
            RTF_TEST_CHECK(std::string(e.what())==std::string("FAILURE"), "exception message");
        }
        catch(std::exception& e) {
            RTF_ASSERT_FAIL("Got wrong exception std::exception");
        }

        RTF_TEST_REPORT("Cheking TestErrorException");
        try {
            throw RTF::TestErrorException(TestMessage("ERROR"));
        }
        catch(RTF::TestErrorException& e) {
            RTF_TEST_CHECK(std::string(e.what())==std::string("ERROR"), "exception message");
        }
        catch(std::exception& e) {
            RTF_ASSERT_FAIL("Got wrong exception std::exception");
        }

        RTF_TEST_REPORT("Cheking FixtureException");
        try {
            throw RTF::FixtureException(TestMessage("FIXTURE"));
        }
        catch(RTF::FixtureException& e) {
            RTF_TEST_CHECK(std::string(e.what())==std::string("FIXTURE"), "exception message");
        }
        catch(std::exception& e) {
            RTF_ASSERT_FAIL("Got wrong exception std::exception");
        }

        RTF_TEST_REPORT("Cheking generic Exception");
        try {
            throw RTF::Exception(TestMessage("GENERIC", "DETAIL", "", 0));
        }
        catch(RTF::Exception& e) {
            RTF::TestMessage msg = e.message();
            RTF_TEST_CHECK(msg.getMessage()==std::string("GENERIC"), "exception message");
            RTF_TEST_CHECK(msg.getDetail() ==std::string("DETAIL"), "exception detalied message");
        }
        catch(std::exception& e) {
            RTF_ASSERT_FAIL("Got wrong exception std::exception");
        }

    }
};

int main(int argc, char** argv)
{
    ConsoleListener listener;
    TestResultCollector collector;
    TestResult result;
    result.addListener(&listener);
    result.addListener(&collector);

    MyTest test;
    test.TestCase::run(result);
    return collector.failedCount();
}
