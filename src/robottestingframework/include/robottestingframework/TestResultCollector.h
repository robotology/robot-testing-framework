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


#ifndef ROBOTTESTINGFRAMEWORK_TESTRESULTCOLLECTOR_H
#define ROBOTTESTINGFRAMEWORK_TESTRESULTCOLLECTOR_H

#include <robottestingframework/ResultEvent.h>
#include <robottestingframework/TestListener.h>

#include <vector>

namespace robottestingframework {

/**
 * \ingroup key_class
 *
 * \brief The TestResultCollector class can be used to store all the events
 * issued by the test cases, suites and runner during the test run.
 * The collected events later can be used by a proper result formatter
 * to be exported as HTML, XML or other desired formats.
 *
 * Here's an example of using a TestResultCollector:
 * \include examples/simple_collector.cpp
 */
class TestResultCollector : public TestListener
{
public:
    typedef std::vector<ResultEvent*> EventResultContainer;
    typedef std::vector<ResultEvent*>::iterator EventResultIterator;

public:
    /**
     * TestResultCollector constructor
     */
    TestResultCollector();

    /**
     *  TestResultCollector destructor
     */
    ~TestResultCollector() override;

    /**
     * @brief reset clear the results
     */
    void reset();

    /**
     * @brief testCount gets the number of test cases. The test
     * suites are not counted.
     * @return the number of tests
     */
    unsigned int testCount();

    /**
     * @brief failedCount gets the number of failed test cases.
     * The test suites are not counted.
     * @return the number of failed tests.
     */
    unsigned int failedCount();

    /**
     * @brief passedCount gets the number of passed test cases.
     * The test suites are not counted.
     * @return the number of passed tests.
     */
    unsigned int passedCount();

    /**
     * @brief suiteCount gets the number of test suites.
     * @return the number of test suites
     */
    unsigned int suiteCount();

    /**
     * @brief failedCount gets the number of failed test suites.
     * @return the number of failed test suites.
     */
    unsigned int failedSuiteCount();

    /**
     * @brief passedCount gets the number of passed test suites.
     * @return the number of passed test suites.
     */
    unsigned int passedSuiteCount();

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
    void addReport(const Test* test, TestMessage msg) override;

    /**
     * This is called when an error occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    void addError(const Test* test, TestMessage msg) override;

    /**
     * This is called when a failure occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding failure message
     */
    void addFailure(const Test* test, TestMessage msg) override;

    /**
     * This is called when a Test is started
     * @param test pointer to the corresponding test
     */
    void startTest(const Test* test) override;

    /**
     * This is called when a Test is finished
     * @param test pointer to the corresponding test
     */
    void endTest(const Test* test) override;

    /**
     * This is called when a TestSuite is started
     * @param test pointer to the corresponding test
     */
    void startTestSuite(const Test* test) override;

    /**
     * This is called when a TestSuite is finished
     * @param test pointer to the corresponding test
     */
    void endTestSuite(const Test* test) override;

private:
    EventResultContainer events;
    unsigned int nTests;
    unsigned int nFailures;
    unsigned int nPasses;
    unsigned int nTestSuites;
    unsigned int nSuiteFailures;
    unsigned int nSuitePasses;
};

} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_TESTRESULTCOLLECTOR_H
