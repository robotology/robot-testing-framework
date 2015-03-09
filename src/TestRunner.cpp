// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <TestRunner.h>

using namespace RTF;


TestRunner::TestRunner() { }


TestRunner::~TestRunner() {
    reset();
}


void TestRunner::addTest(RTF::Test* test) {
    tests.insert(test);
}


void TestRunner::removeTest(RTF::Test* test) {
    tests.erase(test);
}

void TestRunner::reset() {
    tests.clear();
}


void TestRunner::run(RTF::TestResult &result) {
    result.startTestRunner();
    for (TestIterator it=tests.begin(); it!=tests.end(); ++it)
        (*it)->run(result);
    result.endTestRunner();
}
