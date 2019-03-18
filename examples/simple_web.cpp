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
#include <robottestingframework/TestCase.h>
#include <robottestingframework/TestResult.h>
#include <robottestingframework/TestResultCollector.h>
#include <robottestingframework/TestRunner.h>
#include <robottestingframework/TestSuite.h>
#include <robottestingframework/WebProgressListener.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#    include <Windows.h>
#else
#    include <unistd.h>
#endif

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
        srand(time(nullptr));
        for (int i = 0; i < 10; i++) {
            int a = rand() % 10;
            int b = rand() % 10;
            ROBOTTESTINGFRAMEWORK_TEST_REPORT("testing smaller...");
            ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE(a < b, "is not smaller");
#ifdef _WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
        }
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
        srand(time(nullptr));
        for (int i = 0; i < 10; i++) {
            int a = rand() % 10;
            int b = rand() % 10;
            ROBOTTESTINGFRAMEWORK_TEST_REPORT("testing equality...");
            ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE(a == b, "are not equal");
#ifdef _WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
        }
    }
};


int main(int argc, char** argv)
{
    // create a test listener to collect the result
    WebProgressListener web(8080, false);

    // create a collector to get computer readable
    // test results
    TestResultCollector collector;

    // create a test result sand add the listeners
    TestResult result;
    result.addListener(&web);
    result.addListener(&collector);
    printf("To see the test result, open a web browser and type 'http://127.0.0.1:8080'...\n");

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

    // return the number of failed tests
    return collector.failedCount();
}
