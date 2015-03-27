// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_TESTRESULTCOLLECTOR_H
#define _RTF_TESTRESULTCOLLECTOR_H

#include <rtf_config.h>
#include <TestListener.h>
#include <ResultEvent.h>

#include <vector>

namespace RTF {
    class TestResultCollector;
}


/**
 * \ingroup key_class
 *
 * \brief The TestResultCollector class can be used to store all the events
 * issued by the test cases, suits and runner during the test run.
 * The collected events later can be used by a porpoper result formatter
 * to be exported as HTML, XML or other desired formats.
 *
 * Here's an example of using a TestResultCollector:
 * \include examples/simple_collector.cpp
 */
class RTF_API RTF::TestResultCollector : public RTF::TestListener {

public:
    typedef std::vector<RTF::ResultEvent*> EventResultContainer;
    typedef std::vector<RTF::ResultEvent*>::iterator EventResultIterator;

public:

    /**
     * TestResultCollector constructor
     */
    TestResultCollector();

    /**
     *  TestResultCollector destructor
     */
    virtual ~TestResultCollector();

    /**
     * @brief reset clear the results
     */
    void reset();

    /**
     * @brief testCount gets the number of test cases. The test
     * suits are not counted.
     * @return the number of tests
     */
    unsigned int testCount();

    /**
     * @brief failedCount gets the number of failed test cases.
     * The test suits are not counted.
     * @return the number of failed tests.
     */
    unsigned int failedCount();

    /**
     * @brief passedCount gets the number of passed test cases.
     * The test suits are not counted.
     * @return the number of passed tests.
     */
    unsigned int passedCount();

    /**
     * @brief getResults return any result event caught by
     * the TestResultCollector. The events are stored in the
     * ResultEvent format which can be type casted to any subtype event
     * such as ResultEventReport, ResultEventError and etc. to indicate the
     * actual type of the events.
     * @return a EventResultContainer of the events
     */
    EventResultContainer& getResults();

    /**
     * This is called to report any arbitrary message
     * from tests.
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    virtual void addReport(const RTF::Test* test, RTF::TestMessage msg);

    /**
     * This is called when an error occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    virtual void addError(const RTF::Test* test, RTF::TestMessage msg);

    /**
     * This is called when a failure occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding failure message
     */
    virtual void addFailure(const RTF::Test* test, RTF::TestMessage msg);

    /**
     * This is called when a Test is started
     * @param test pointer to the corresponding test
     */
    virtual void startTest(const RTF::Test* test);

    /**
     * This is called when a Test is finished
     * @param test pointer to the corresponding test
     */
    virtual void endTest(const RTF::Test* test);

    /**
     * This is called when a TestSuit is started
     * @param test pointer to the corresponding test
     */
    virtual void startTestSuit(const RTF::Test* test);

    /**
     * This is called when a TestSuit is finished
     * @param test pointer to the corresponding test
     */
    virtual void endTestSuit(const RTF::Test* test);

private:
    EventResultContainer events;
    unsigned int nTests;
    unsigned int nFailures;
    unsigned int nPasses;
};
#endif // _RTF_TESTRESULTCOLLECTOR_H
