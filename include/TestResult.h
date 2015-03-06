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

#include <vector>

namespace RTF {
    class TestResult;
}


/**
 * class TestResult
 */

class RTF::TestResult {
    //typedef std::vector<RTF::TestListener* listener>

public:

    /**
     * TestResult constructor
     */
    TestResult() { }

    /**
     *  TestResult destructor
     */
    virtual ~TestResult() { }


    /**
     * This is called when an error occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    virtual void addError(RTF::Test* test, RTF::TestMessage msg) {}

    /**
     * This is called when a failure occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding failure message
     */
    virtual void addFailure(RTF::Test* test, RTF::TestMessage msg) {}

    /**
     * This is called when a Test is started
     * @param test pointer to the corresponding test
     */
    virtual void startTest(RTF::Test* test) {}

    /**
     * This is called when a Test is finished
     * @param test pointer to the corresponding test
     */
    virtual void endTest(RTF::Test* test) {}

    /**
     * This is called when a TestSuit is started
     * @param test pointer to the corresponding test
     */
    virtual void startTestSuit(RTF::Test* test) {}

    /**
     * This is called when a TestSuit is finished
     * @param test pointer to the corresponding test
     */
    virtual void endTestSuit(RTF::Test* test) {}

    /**
     * This is called when the TestRunner is started
     */
    virtual void startTestRunner() {}

    /**
     * This is called when the TestRunner is finished
     */
    virtual void endTestRunner() {}
};
#endif // _RTF_TESTResult_H
