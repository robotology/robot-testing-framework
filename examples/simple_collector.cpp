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
#include <robottestingframework/TestRunner.h>
#include <robottestingframework/TestSuite.h>
#include <robottestingframework/TextOutputter.h>

#include <cstdio>

using namespace robottestingframework;

class MyTest1 : public TestCase
{
public:
    MyTest1() :
            TestCase("MyTest1")
    {
    }

    void run() override
    {
        ROBOTTESTINGFRAMEWORK_TEST_REPORT("testing smaller");
        ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE(3 < 5, "is not smaller");
    }
};

class MyTest2 : public TestCase
{
public:
    MyTest2() :
            TestCase("MyTest2")
    {
    }

    void run() override
    {
        ROBOTTESTINGFRAMEWORK_TEST_REPORT("testing equality");
        ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE(5 == 3, "are not equal");
    }
};


int main(int argc, char** argv)
{
    // create a test listener to print out the result
    ConsoleListener listener(false);

    // create a test result collector to collect the result
    TestResultCollector collector;

    // create a test result and add the listeners
    TestResult result;
    result.addListener(&listener);
    result.addListener(&collector);


    // create a test suite and the test cases
    TestSuite suite("MyTestSuite");
    MyTest1 test1;
    MyTest2 test2;
    suite.addTest(&test1);
    suite.addTest(&test2);

    // create a test runner
    TestRunner runner;
    runner.addTest(&suite);
    runner.run(result);

    // print out some simple statistics
    printf("\n-------- results ---------\n");
    printf("Total number of tests : %d\n", collector.testCount());
    printf("Number of passed tests: %d\n", collector.passedCount());
    printf("Number of failed tests: %d\n", collector.failedCount());

    // store the results in a text file
    TextOutputter outputter(collector);
    outputter.write("./result.txt", true);

    // return the number of failed tests
    return collector.failedCount();
}
