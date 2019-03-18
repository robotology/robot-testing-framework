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


#ifndef ROBOTTESTINGFRAMEWORK_TESTSUITE_H
#define ROBOTTESTINGFRAMEWORK_TESTSUITE_H

#include <robottestingframework/FixtureManager.h>
#include <robottestingframework/Test.h>
#include <robottestingframework/TestMessage.h>
#include <robottestingframework/TestResult.h>

#include <vector>

namespace robottestingframework {

/**
 * \ingroup key_class
 *
 * \brief The TestSuite holds a group of tests. When the \c run() method of a
 * TestSuite is called, it executes all its tests. A TestSuite can also has a FixtureManager.
 * In this case, it calls the \c setup() method of FixtureManager to setup any fixture which
 * is required for the tests before executing the tests. After running all the tests, the \c tearDown()
 * method of the FixtureManager is called to tear down the fixture.
 *
 * The \c fixtureCollapsed method is used by a fixture manager to inform the test suit
 * that the corresponding fixture has been collapsed. In this case, an exception is thrown
 * by the TestSuite and the remaining tests will not be executed any more.  This method can be
 * also overriden by a subclass if any specific action is required to be taken (such as retrying
 * to setup the fixture and runing the reamining tests) upon collapsing the fixture.
 *
 * Here's an example of using a TestSuite:
 * \include examples/simple_suite.cpp
 */
class TestSuite :
        public Test,
        public FixtureEvents
{

    typedef std::vector<Test*> TestContainer;
    typedef std::vector<Test*>::iterator TestIterator;
    typedef std::vector<FixtureManager*> FixtureContainer;
    typedef std::vector<FixtureManager*>::iterator FixtureIterator;
    typedef std::vector<FixtureManager*>::reverse_iterator FixtureRIterator;

public:
    /**
     * TestSuite constructor
     * @param  name The TestSuite name
     */
    TestSuite(std::string name);

    /**
     *  TestSuite destructor
     */
    virtual ~TestSuite();

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
     * @brief addFixtureManager  add a fixture manager for
     * the current test suite.
     * @param manager an instance of FixtureManager
     */
    void addFixtureManager(FixtureManager* manager);

    /**
     * @brief fixtureCollapsed is called by a fixture manager
     *        (if it is already setup) to inform the test suit
     *        that the corresponding fixture has been collapsed.
     * @param reason An error message indicates the reason for
     *        collapsing the fixture.
     */
    void fixtureCollapsed(TestMessage reason) override;

    /**
     * the main caller of a TestSuite inherited from Test Class.
     * @param result an instance of a TestResult
     * to collect the result of the test.
     */
    void run(TestResult& rsl) override;

    /**
     * @brief interrupt interrupts the current test run
     */
    void interrupt() override;

    /**
     * @brief succeeded
     * @return true or false representing whether the test
     * was successful or not.
     */
    bool succeeded() const override;

    /**
     * @brief getResult returns an instance of TestResult
     * if run(TestResult &result) has been already called
     * by a TestRunner
     * @return an instance of TestResult
     */
    TestResult* getResult();

    /**
     * @brief returns the number of tests in this suite
     * @return the number of tests in this suite
     */
    std::size_t size() const;

protected:
    /**
     * @brief setup is called before the test run
     * @return true or false depending of the test initialization
     */
    virtual bool setup();

    /**
     * @brief tearDown is called after the test run
     */
    virtual void tearDown();

private:
    Test* current;
    TestResult* result;
    bool successful;
    bool fixtureOK;
    bool interrupted;
    TestMessage fixtureMessage;
    FixtureContainer fixtureManagers;
    TestContainer tests;
};

} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_TESTSUITE_H
