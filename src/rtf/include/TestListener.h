// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_TESTLISTENER_H
#define _RTF_TESTLISTENER_H

#include <Test.h>
#include <TestMessage.h>

namespace RTF {
    class TestListener;
}


/**
 * @brief The base class of any test result listeners
 */
class RTF::TestListener {
public:

    /**
     * TestListener constructor
     */
    TestListener() { }

    /**
     *  TestListener destructor
     */
    virtual ~TestListener() { }

    /**
     * This is called to report any arbitrary message
     * from tests.
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    virtual void addReport(const RTF::Test* test, RTF::TestMessage msg) {}

    /**
     * This is called when an error occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    virtual void addError(const RTF::Test* test, RTF::TestMessage msg) {}

    /**
     * This is called when a failure occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding failure message
     */
    virtual void addFailure(const RTF::Test* test, RTF::TestMessage msg) {}

    /**
     * This is called when a Test is started
     * @param test pointer to the corresponding test
     */
    virtual void startTest(const RTF::Test* test) {}

    /**
     * This is called when a Test is finished
     * @param test pointer to the corresponding test
     */
    virtual void endTest(const RTF::Test* test) {}

    /**
     * This is called when a TestSuit is started
     * @param test pointer to the corresponding test
     */
    virtual void startTestSuit(const RTF::Test* test) {}

    /**
     * This is called when a TestSuit is finished
     * @param test pointer to the corresponding test
     */
    virtual void endTestSuit(const RTF::Test* test) {}

    /**
     * This is called when the TestRunner is started
     */
    virtual void startTestRunner() {}

    /**
     * This is called when the TestRunner is finished
     */
    virtual void endTestRunner() {}
};
#endif // _RTF_TESTLISTENER_H
