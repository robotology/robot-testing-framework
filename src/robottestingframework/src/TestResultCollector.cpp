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


#include <robottestingframework/TestResultCollector.h>

using namespace robottestingframework;

TestResultCollector::TestResultCollector()
{
    nPasses = nFailures = nTests = 0;
    nSuitePasses = nSuiteFailures = nTestSuites = 0;
}

TestResultCollector::~TestResultCollector()
{
    reset();
}

void TestResultCollector::reset()
{
    nPasses = nFailures = nTests = 0;
    TestResultCollector::EventResultIterator it;
    for (it = events.begin(); it != events.end(); ++it) {
        delete *(it);
    }
    events.clear();
}

unsigned int TestResultCollector::testCount()
{
    return nTests;
}

unsigned int TestResultCollector::failedCount()
{
    return nFailures;
}

unsigned int TestResultCollector::passedCount()
{
    return nPasses;
}

unsigned int TestResultCollector::suiteCount()
{
    return nTestSuites;
}

unsigned int TestResultCollector::failedSuiteCount()
{
    return nSuiteFailures;
}

unsigned int TestResultCollector::passedSuiteCount()
{
    return nSuitePasses;
}

TestResultCollector::EventResultContainer& TestResultCollector::getResults()
{
    return events;
}

void TestResultCollector::addReport(const Test* test,
                                    TestMessage msg)
{
    events.push_back(new ResultEventReport(test, msg));
}

void TestResultCollector::addError(const Test* test,
                                   TestMessage msg)
{
    events.push_back(new ResultEventError(test, msg));
}


void TestResultCollector::addFailure(const Test* test,
                                     TestMessage msg)
{
    events.push_back(new ResultEventFailure(test, msg));
}


void TestResultCollector::startTest(const Test* test)
{
    nTests++;
    events.push_back(new ResultEventStartTest(test,
                                              TestMessage("started")));
}


void TestResultCollector::endTest(const Test* test)
{
    (test->succeeded()) ? nPasses++ : nFailures++;
    events.push_back(new ResultEventEndTest(test,
                                            TestMessage("ended")));
}


void TestResultCollector::startTestSuite(const Test* test)
{
    nTestSuites++;
    events.push_back(new ResultEventStartSuite(test,
                                               TestMessage("started")));
}


void TestResultCollector::endTestSuite(const Test* test)
{

    (test->succeeded()) ? nSuitePasses++ : nSuiteFailures++;
    events.push_back(new ResultEventEndSuite(test,
                                             TestMessage("ended")));
}
