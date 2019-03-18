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
#include <robottestingframework/TestAssert.h>
#include <robottestingframework/TestCase.h>
#include <robottestingframework/TestResult.h>
#include <robottestingframework/TestResultCollector.h>

#include <iostream>
#include <stdio.h>

using namespace robottestingframework;

class MyTest : public TestCase
{
public:
    MyTest() :
            TestCase("MyTest")
    {
    }

    bool setup(int argc, char** argv) override
    {
        ROBOTTESTINGFRAMEWORK_TEST_REPORT("running MyTest::setup...");
        return true;
    }

    void tearDown() override
    {
        ROBOTTESTINGFRAMEWORK_TEST_REPORT("running MyTest::teardown...");
        ROBOTTESTINGFRAMEWORK_ASSERT_ERROR("this is just for example!");
    }

    void run() override
    {
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(2 < 3, "two is less than three");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(2 == 3, "two is equal to three");
        int a = 5;
        int b = 3;
        ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE(a < b, Asserter::format("%d is not smaller than %d.", a, b));
    }
};

int main(int argc, char** argv)
{
    // create a test listener to collect the result
    // and enable the verbose mode
    ConsoleListener listener(true);

    // create a collector to get computer readable
    // test results
    TestResultCollector collector;

    // create a test result and add the listeners
    TestResult result;
    result.addListener(&listener);
    result.addListener(&collector);

    // calling a test case
    MyTest atest;
    atest.TestCase::run(result);

    // return 0 if the test passed
    // otherwise the number of failed test
    return collector.failedCount();
}
