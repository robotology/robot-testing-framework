// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_TESTRESULT_H
#define _RTF_TESTRESULT_H

#include <Test.h>
#include <TestMessage.h>
#include <TestListener.h>

#include <set>

namespace RTF {
    class TestResult;
}



/**
 * class TestResult
 * \ingroup key_class
 *
 * \brief The TestResult class is used to deliver the test results including
 * any error and failures produced by tests to any listiners. The listeneres
 * can be added by \c addListener.
 *
 * Here's an example of using a TestResult:
 * \include examples/simple.cpp
 */
class RTF::TestResult {

    typedef std::set<RTF::TestListener*>  ListenerContainer;
    typedef std::set<RTF::TestListener*>::iterator ListenerIterator;


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
    void addListener(RTF::TestListener* listener);

    /**
     * Remove a listener
     * @param listener pointer to a TestListener object
     */
    void removeListener(RTF::TestListener* listener);

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
    void addReport(const RTF::Test* test, RTF::TestMessage msg);

    /**
     * This is called when an error occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    void addError(const RTF::Test* test, RTF::TestMessage msg);

    /**
     * This is called when a failure occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding failure message
     */
    void addFailure(const RTF::Test* test, RTF::TestMessage msg);

    /**
     * This is called when a Test is started
     * @param test pointer to the corresponding test
     */
    void startTest(const RTF::Test* test);

    /**
     * This is called when a Test is finished
     * @param test pointer to the corresponding test
     */
    void endTest(const RTF::Test* test);

    /**
     * This is called when a TestSuit is started
     * @param test pointer to the corresponding test
     */
    void startTestSuit(const RTF::Test* test);

    /**
     * This is called when a TestSuit is finished
     * @param test pointer to the corresponding test
     */
    void endTestSuit(const RTF::Test *test);

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
#endif // _RTF_TESTResult_H
