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


#include <robottestingframework/TestAssert.h>
#include <robottestingframework/TestResultCollector.h>
#include <robottestingframework/TestRunner.h>
#include <robottestingframework/dll/Plugin.h>

using namespace robottestingframework;


class MyTest : public TestCase
{
public:
    MyTest() :
            TestCase("MyTest")
    {
    }

    void run() override
    {
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(2 < 3, "two is less than three");
    }
};


class MyTest2 : public TestCase
{
public:
    MyTest2() :
            TestCase("MyTest")
    {
    }

    void run() override
    {
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(2 == 3, "two is equal to three");
    }
};


class MultiTestCases : public TestCase
{
public:
    MultiTestCases() :
            TestCase("MultiTestCases")
    {
    }

    void run() override
    {
        TestResultCollector collector;

        // create a test result and add the listeners
        TestResult result;
        result.addListener(&collector);

        // create a test runner
        TestRunner runner;
        MyTest test1;
        MyTest2 test2;
        runner.addTest(&test1);
        runner.addTest(&test2);
        runner.run(result);

        //ROBOTTESTINGFRAMEWORK_TEST_REPORT(Asserter::format("count: %d", collector.failedCount()));
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.testCount() == 2, "Checking tests count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.passedCount() == 1, "Checking passed count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.failedCount() == 1, "Checking failed count");
    }
};

ROBOTTESTINGFRAMEWORK_PREPARE_PLUGIN(MultiTestCases)
