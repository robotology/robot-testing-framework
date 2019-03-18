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


#ifndef ROBOTTESTINGFRAMEWORK_TESTRUNNER_H
#define ROBOTTESTINGFRAMEWORK_TESTRUNNER_H

#include <robottestingframework/Test.h>
#include <robottestingframework/TestResult.h>

#include <vector>

namespace robottestingframework {

/**
 * \ingroup key_class
 *
 * \brief The TestRunner class runs the tests added as TestCase or TestSuite.
 * It simply goes through a list of the tests and run them one after each other.
 *
 * Here's an example of using a TestRunner:
 * \include examples/simple_runner.cpp
 */
class TestRunner
{

    typedef std::vector<Test*> TestContainer;
    typedef std::vector<Test*>::iterator TestIterator;


public:
    /**
     * TestRunner constructor
     */
    TestRunner();

    /**
     *  TestRunner destructor
     */
    virtual ~TestRunner();

    /**
     * Adding a new test
     * @param test pointer to a Test object
     */
    void addTest(Test* test);

    /**
     * Remove a test
     * @param test pointer to a Test object
     */
    void removeTest(Test* test);

    /**
     * Clear the test list
     */
    void reset();

    /**
     * Run all the tests in the list
     * @param result an instance of a TestResult
     * to collect the result of the test.
     */
    void run(TestResult& result);

    /**
     * @brief interrupt interrupts the current test run
     */
    void interrupt();

private:
    TestContainer tests;
    Test* current;
    bool interrupted;
};

} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_TESTRUNNER_H
