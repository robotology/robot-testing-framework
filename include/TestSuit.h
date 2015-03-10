// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_TESTSUIT_H
#define _RTF_TESTSUIT_H

#include <Test.h>
#include <TestResult.h>
#include <TestMessage.h>
#include <FixtureManager.h>
#include <set>

namespace RTF {
    class TestSuit;
}


/**
 * class TestSuit
 */

class RTF::TestSuit : public RTF::Test, public RTF::FixtureEvents {

    typedef std::set<RTF::Test*> TestContainer;
    typedef std::set<RTF::Test*>::iterator TestIterator;

public:

    /**
     * TestSuit constructor
     * @param  name The TestSuit name
     */
    TestSuit(std::string name);

    /**
     *  TestSuit destructor
     */
    virtual ~TestSuit();

    /**
     * Adding a new test
     * @param test pointer to a Test object
     */
    void addTest(RTF::Test* test);

    /**
     * Remove a test
     * @param test pointer to a Test object
     */
    void removeTest(RTF::Test* test);

    /**
     * Clear the test list
     */
    void reset();

    /**
     * @brief setFixtureManager  setup a fixture manager for
     * the current test suit.
     * @param manager an instance of FixtureManager
     */
    void setFixtureManager(RTF::FixtureManager* manager);

    /**
     * @brief fixtureCollapsed is called by a fixture manager
     *        (if it is already setup) to inform the test suit
     *        that the corresponding fixture has been collapsed.
     * @param reason An error message indicates the reason for
     *        collapsing the fixture.
     */
    virtual void fixtureCollapsed(RTF::TestMessage reason);

    /**
     * the main caller of a TestSuit inherited from Test Class.
     * @param result an instance of a TestResult
     * to collect the result of the test.
     */
    virtual void run(TestResult &result);

    /**
     * @brief succeeded
     * @return true or false representing whether the test
     * was successful or not.
     */
    bool succeeded() const;

    /**
     * @brief getResult returns an instance of TestResult
     * if run(TestResult &result) has been already called
     * by a TestRunner
     * @return an instance of TestResult
     */
    RTF::TestResult* getResult();

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
    RTF::TestResult* result;
    bool successful;
    bool fixtureOK;
    RTF::TestMessage fixtureMesssage;
    RTF::FixtureManager* fixtureManager;
    TestContainer tests;
};
#endif // _RTF_TESTSUIT_H
