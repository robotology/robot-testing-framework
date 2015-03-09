// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_TESTRUNNER_H
#define _RTF_TESTRUNNER_H

#include <Test.h>
#include <TestResult.h>

#include <set>

namespace RTF {
    class TestRunner;
}


/**
 * class TestRunner
 */

class RTF::TestRunner {

    typedef std::set<RTF::Test*> TestContainer;
    typedef std::set<RTF::Test*>::iterator TestIterator;


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
     * Run all the tests in the list
     * @param result an instance of a TestResult
     * to collect the result of the test.
     */
    void run(TestResult &result);

private:
    TestContainer tests;
};
#endif // _RTF_TESTRUNNER_H
