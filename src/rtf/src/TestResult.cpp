// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <rtf/TestResult.h>

using namespace RTF;

#define CALL_LISTENERS(method, ...)\
    for (ListenerIterator it=listeners.begin(); it!=listeners.end(); ++it)\
        (*it)->method(__VA_ARGS__);

TestResult::TestResult() {

}


TestResult::~TestResult() {
    reset();
}


void TestResult::addListener(RTF::TestListener* listener) {
    listeners.insert(listener);
}


void TestResult::removeListener(RTF::TestListener* listener) {
    listeners.erase(listener);
}


void TestResult::reset() {
    listeners.clear();
}

void TestResult::addReport(const RTF::Test* test, RTF::TestMessage msg) {
    CALL_LISTENERS(addReport, test, msg);
}

void TestResult::addError(const RTF::Test* test, RTF::TestMessage msg) {
    CALL_LISTENERS(addError, test, msg);
}

void TestResult::addFailure(const RTF::Test* test, RTF::TestMessage msg) {
    CALL_LISTENERS(addFailure, test, msg);
}

void TestResult::startTest(const RTF::Test* test) {
    CALL_LISTENERS(startTest, test);
}

void TestResult::endTest(const Test *test) {
    CALL_LISTENERS(endTest, test);
}

void TestResult::startTestSuit(const RTF::Test* test) {
    CALL_LISTENERS(startTestSuit, test);
}

void TestResult::endTestSuit(const RTF::Test* test) {
    CALL_LISTENERS(endTestSuit, test);
}

void TestResult::startTestRunner() {
    CALL_LISTENERS(startTestRunner);
}

void TestResult::endTestRunner() {
    CALL_LISTENERS(endTestRunner);
}
