// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <iostream>
#include <rtf/TestCase.h>
#include <rtf/TestResult.h>
#include <rtf/TestResultCollector.h>
#include <rtf/ConsoleListener.h>
#include <rtf/Asserter.h>
#include <rtf/TestAssert.h>


using namespace RTF;

class TestCheck : public TestCase {

public:
    size_t exCount;
    TestCheck() : TestCase("TestCheck") { exCount = 0;}
    virtual void run() {

        try {
            Asserter::testCheck(true, RTF::TestMessage("true"), this);
        }
        catch(std::exception& e) {
            exCount++;
        }

        try {
            Asserter::testCheck(false, RTF::TestMessage("false"), this);
        }
        catch(std::exception& e) {
            exCount++;
        }
    }
};

class TestFail : public TestCase {

public:
    size_t exCount;
    TestFail() : TestCase("TestFail") { exCount = 0;}
    virtual void run() {

        try {
            Asserter::testFail(true, RTF::TestMessage("true"), this);
        }
        catch(std::exception& e) {
            exCount++;
        }

        try {
            Asserter::testFail(false, RTF::TestMessage("false"), this);
        }
        catch(std::exception& e) {
            exCount++;
        }
    }
};


class MyTest : public TestCase {
public:
    MyTest() : TestCase("AsserterTest") { }

    virtual void run() {

        RTF_TEST_REPORT("Cheking Asserter::fail");
        try {
            Asserter::fail(true, TestMessage("TRUE"));
            Asserter::fail(false, TestMessage("FALSE"));
        }
        catch(RTF::TestFailureException& e) {
            RTF_TEST_FAIL_IF(std::string(e.what())==std::string("FALSE"), "exception message");
        }
        catch(std::exception& e) {
            RTF_ASSERT_FAIL("Got wrong exception std::exception");
        }

        RTF_TEST_REPORT("Cheking Asserter::error");
        try {
            Asserter::error(true, TestMessage("TRUE"));
            Asserter::error(false, TestMessage("FALSE"));
        }
        catch(RTF::TestErrorException& e) {
            RTF_TEST_FAIL_IF(std::string(e.what())==std::string("FALSE"), "exception message");
        }
        catch(std::exception& e) {
            RTF_ASSERT_FAIL("Got wrong exception std::exception");
        }

        RTF_TEST_REPORT("Cheking Asserter::testCheck");
        TestResultCollector collector;
        TestResult result;
        result.addListener(&collector);
        TestCheck check;
        check.TestCase::run(result);
        RTF_TEST_CHECK(collector.failedCount()==1, "Cheking Asserter::testCheck for failures count");
        RTF_TEST_CHECK(check.exCount==0, "Cheking Asserter::testCheck for exceptions count");

        RTF_TEST_REPORT("Cheking Asserter::testFail");
        collector.reset();
        RTF_TEST_CHECK(collector.failedCount()==0, "Cheking collector.reset()");
        TestFail fail;
        fail.TestCase::run(result);
        RTF_TEST_CHECK(collector.failedCount()==1, "Cheking Asserter::testFail for failures count");
        RTF_TEST_CHECK(fail.exCount==0, "Cheking Asserter::testFail for exceptions count");
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
