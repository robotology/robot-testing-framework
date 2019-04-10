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


#include <robottestingframework/ConsoleListener.h>
#include <robottestingframework/Exception.h>
#include <robottestingframework/TestAssert.h>
#include <robottestingframework/TestCase.h>
#include <robottestingframework/TestResult.h>
#include <robottestingframework/TestResultCollector.h>


using namespace robottestingframework;

class MyTest : public TestCase
{
public:
    MyTest() :
            TestCase("ExceptionTest")
    {
    }

    void run() override
    {

        ROBOTTESTINGFRAMEWORK_TEST_REPORT("Cheking TestFailureException");
        try {
            throw TestFailureException(TestMessage("FAILURE"));
        } catch (TestFailureException& e) {
            ROBOTTESTINGFRAMEWORK_TEST_CHECK(std::string(e.what()) == std::string("FAILURE"), "exception message");
        } catch (std::exception& e) {
            ROBOTTESTINGFRAMEWORK_ASSERT_FAIL("Got wrong exception std::exception");
        }

        ROBOTTESTINGFRAMEWORK_TEST_REPORT("Cheking TestErrorException");
        try {
            throw TestErrorException(TestMessage("ERROR"));
        } catch (TestErrorException& e) {
            ROBOTTESTINGFRAMEWORK_TEST_CHECK(std::string(e.what()) == std::string("ERROR"), "exception message");
        } catch (std::exception& e) {
            ROBOTTESTINGFRAMEWORK_ASSERT_FAIL("Got wrong exception std::exception");
        }

        ROBOTTESTINGFRAMEWORK_TEST_REPORT("Cheking FixtureException");
        try {
            throw FixtureException(TestMessage("FIXTURE"));
        } catch (FixtureException& e) {
            ROBOTTESTINGFRAMEWORK_TEST_CHECK(std::string(e.what()) == std::string("FIXTURE"), "exception message");
        } catch (std::exception& e) {
            ROBOTTESTINGFRAMEWORK_ASSERT_FAIL("Got wrong exception std::exception");
        }

        ROBOTTESTINGFRAMEWORK_TEST_REPORT("Cheking generic Exception");
        try {
            throw Exception(TestMessage("GENERIC", "DETAIL", "", 0));
        } catch (Exception& e) {
            TestMessage msg = e.message();
            ROBOTTESTINGFRAMEWORK_TEST_CHECK(msg.getMessage() == std::string("GENERIC"), "exception message");
            ROBOTTESTINGFRAMEWORK_TEST_CHECK(msg.getDetail() == std::string("DETAIL"), "exception detalied message");
        } catch (std::exception& e) {
            ROBOTTESTINGFRAMEWORK_ASSERT_FAIL("Got wrong exception std::exception");
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
