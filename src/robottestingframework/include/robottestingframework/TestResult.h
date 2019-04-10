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


#ifndef ROBOTTESTINGFRAMEWORK_TESTRESULT_H
#define ROBOTTESTINGFRAMEWORK_TESTRESULT_H

#include <robottestingframework/Test.h>
#include <robottestingframework/TestListener.h>
#include <robottestingframework/TestMessage.h>

#include <set>

namespace robottestingframework {

/**
 * \ingroup key_class
 *
 * \brief The TestResult class is used to deliver the test results including
 * any error and failures produced by tests to any listener. The listeneres
 * can be added by \c addListener.
 *
 * Here's an example of using a TestResult:
 * \include examples/simple.cpp
 */
class TestResult
{
    typedef std::set<TestListener*> ListenerContainer;
    typedef std::set<TestListener*>::iterator ListenerIterator;

public:
    /**
     * TestResult constructor
     */
    TestResult();

    /**
     *  TestResult destructor
     */
    virtual ~TestResult();

    /**
     * Adding a new listener
     * @param listener pointer to a TestListener object
     */
    void addListener(TestListener* listener);

    /**
     * Remove a listener
     * @param listener pointer to a TestListener object
     */
    void removeListener(TestListener* listener);

    /**
     * Clear the listener list
     */
    void reset();

    /**
     * This is called to report any arbitrary message
     * from tests.
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    void addReport(const Test* test, TestMessage msg);

    /**
     * This is called when an error occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    void addError(const Test* test, TestMessage msg);

    /**
     * This is called when a failure occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding failure message
     */
    void addFailure(const Test* test, TestMessage msg);

    /**
     * This is called when a Test is started
     * @param test pointer to the corresponding test
     */
    void startTest(const Test* test);

    /**
     * This is called when a Test is finished
     * @param test pointer to the corresponding test
     */
    void endTest(const Test* test);

    /**
     * This is called when a TestSuite is started
     * @param test pointer to the corresponding test
     */
    void startTestSuite(const Test* test);

    /**
     * This is called when a TestSuite is finished
     * @param test pointer to the corresponding test
     */
    void endTestSuite(const Test* test);

    /**
     * This is called when the TestRunner is started
     */
    void startTestRunner();

    /**
     * This is called when the TestRunner is finished
     */
    void endTestRunner();

private:
    ListenerContainer listeners;
};

} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_TESTResult_H
