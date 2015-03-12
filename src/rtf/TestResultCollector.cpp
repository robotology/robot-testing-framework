// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <TestResultCollector.h>

using namespace RTF;

TestResultCollector::TestResultCollector() {
    nPasses = nFailures = nTests = 0;
}

TestResultCollector::~TestResultCollector() {
    reset();
}

void TestResultCollector::reset() {
    nPasses = nFailures = nTests = 0;
    TestResultCollector::EventResultIterator it;
    for(it=events.begin(); it!=events.end(); ++it) {
        delete *(it);
    }
    events.clear();
}

unsigned int TestResultCollector::testCount() {
    return nTests;
}

unsigned int TestResultCollector::failedCount() {
    return nFailures;
}

unsigned int TestResultCollector::passedCount() {
    return nPasses;
}

TestResultCollector::EventResultContainer& TestResultCollector::getResults() {
    return events;
}

void TestResultCollector::addReport(const RTF::Test* test,
                                    RTF::TestMessage msg) {
    events.push_back(new ResultEventReport(test, msg));
}

void TestResultCollector::addError(const RTF::Test* test,
                                   RTF::TestMessage msg) {
    events.push_back(new ResultEventError(test, msg));
}


void TestResultCollector::addFailure(const RTF::Test* test,
                                     RTF::TestMessage msg) {
    events.push_back(new ResultEventFailure(test, msg));
}


void TestResultCollector::startTest(const RTF::Test* test) {
    nTests++;
    events.push_back(new ResultEventStartTest(test,
                                              TestMessage("started")));
}


void TestResultCollector::endTest(const RTF::Test* test) {
    if(test->succeeded())
        nPasses++;
    else
        nFailures++;
    events.push_back(new ResultEventEndTest(test,
                                            TestMessage("ended")));
}


void TestResultCollector::startTestSuit(const RTF::Test* test) {
    events.push_back(new ResultEventStartSuit(test,
                                              TestMessage("started")));
}


void TestResultCollector::endTestSuit(const RTF::Test* test) {
    events.push_back(new ResultEventEndSuit(test,
                                            TestMessage("ended")));
}
