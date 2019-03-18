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


#ifndef ROBOTTESTINGFRAMEWORK_TESTLISTENER_H
#define ROBOTTESTINGFRAMEWORK_TESTLISTENER_H

#include <robottestingframework/Test.h>
#include <robottestingframework/TestMessage.h>

namespace robottestingframework {

/**
 * @brief The base class of any test result listeners
 */
class TestListener
{
public:
    /**
     * TestListener constructor
     */
    TestListener() = default;

    /**
     *  TestListener destructor
     */
    virtual ~TestListener() = default;

    /**
     * This is called to report any arbitrary message
     * from tests.
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    virtual void addReport(const Test* test, TestMessage msg)
    {
    }

    /**
     * This is called when an error occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    virtual void addError(const Test* test, TestMessage msg)
    {
    }

    /**
     * This is called when a failure occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding failure message
     */
    virtual void addFailure(const Test* test, TestMessage msg)
    {
    }

    /**
     * This is called when a Test is started
     * @param test pointer to the corresponding test
     */
    virtual void startTest(const Test* test)
    {
    }

    /**
     * This is called when a Test is finished
     * @param test pointer to the corresponding test
     */
    virtual void endTest(const Test* test)
    {
    }

    /**
     * This is called when a TestSuite is started
     * @param test pointer to the corresponding test
     */
    virtual void startTestSuite(const Test* test)
    {
    }

    /**
     * This is called when a TestSuite is finished
     * @param test pointer to the corresponding test
     */
    virtual void endTestSuite(const Test* test)
    {
    }

    /**
     * This is called when the TestRunner is started
     */
    virtual void startTestRunner()
    {
    }

    /**
     * This is called when the TestRunner is finished
     */
    virtual void endTestRunner()
    {
    }
};

} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_TESTLISTENER_H
