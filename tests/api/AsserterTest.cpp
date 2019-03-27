/*
 * Robot Testing Framework
 *
 * Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include <robottestingframework/Asserter.h>
#include <robottestingframework/ConsoleListener.h>
#include <robottestingframework/TestAssert.h>
#include <robottestingframework/TestCase.h>
#include <robottestingframework/TestResult.h>
#include <robottestingframework/TestResultCollector.h>

#include <iostream>


using namespace robottestingframework;

class TestCheck : public TestCase
{

public:
    size_t exCount;
    TestCheck() :
            TestCase("TestCheck")
    {
        exCount = 0;
    }
    void run() override
    {

        try {
            Asserter::testCheck(true, TestMessage("true"), this);
        } catch (std::exception& e) {
            exCount++;
        }

        try {
            Asserter::testCheck(false, TestMessage("false"), this);
        } catch (std::exception& e) {
            exCount++;
        }
    }
};

class TestFail : public TestCase
{

public:
    size_t exCount;
    TestFail() :
            TestCase("TestFail")
    {
        exCount = 0;
    }
    void run() override
    {

        try {
            Asserter::testFail(true, TestMessage("true"), this);
        } catch (std::exception& e) {
            exCount++;
        }

        try {
            Asserter::testFail(false, TestMessage("false"), this);
        } catch (std::exception& e) {
            exCount++;
        }
    }
};


class MyTest : public TestCase
{
public:
    MyTest() :
            TestCase("AsserterTest")
    {
    }

    void run() override
    {

        ROBOTTESTINGFRAMEWORK_TEST_REPORT("Cheking Asserter::fail");
        try {
            Asserter::fail(true, TestMessage("TRUE"));
            Asserter::fail(false, TestMessage("FALSE"));
        } catch (TestFailureException& e) {
            ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE(std::string(e.what()) == std::string("FALSE"), "exception message");
        } catch (std::exception& e) {
            ROBOTTESTINGFRAMEWORK_ASSERT_FAIL("Got wrong exception std::exception");
        }

        ROBOTTESTINGFRAMEWORK_TEST_REPORT("Cheking Asserter::error");
        try {
            Asserter::error(true, TestMessage("TRUE"));
            Asserter::error(false, TestMessage("FALSE"));
        } catch (TestErrorException& e) {
            ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE(std::string(e.what()) == std::string("FALSE"), "exception message");
        } catch (std::exception& e) {
            ROBOTTESTINGFRAMEWORK_ASSERT_FAIL("Got wrong exception std::exception");
        }

        ROBOTTESTINGFRAMEWORK_TEST_REPORT("Cheking Asserter::testCheck");
        TestResultCollector collector;
        TestResult result;
        result.addListener(&collector);
        TestCheck check;
        check.TestCase::run(result);
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.failedCount() == 1, "Cheking Asserter::testCheck for failures count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(check.exCount == 0, "Cheking Asserter::testCheck for exceptions count");

        ROBOTTESTINGFRAMEWORK_TEST_REPORT("Cheking Asserter::testFail");
        collector.reset();
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.failedCount() == 0, "Cheking collector.reset()");
        TestFail fail;
        fail.TestCase::run(result);
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.failedCount() == 1, "Cheking Asserter::testFail for failures count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(fail.exCount == 0, "Cheking Asserter::testFail for exceptions count");
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
