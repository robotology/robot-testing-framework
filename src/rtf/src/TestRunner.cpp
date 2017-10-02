// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <rtf/TestRunner.h>
#include <algorithm>

using namespace RTF;


TestRunner::TestRunner()
    : current(NULL) { }


TestRunner::~TestRunner() {
    reset();
}


void TestRunner::addTest(RTF::Test* test) {
    if (std::find(tests.begin(), tests.end(), test) == tests.end())
    {
        tests.push_back(test);
    }
}


void TestRunner::removeTest(RTF::Test* test) {
    for (size_t i = 0; i < tests.size(); i++)
    {
        tests.erase(tests.begin() + i);
    }
    
}

void TestRunner::reset() {
    tests.clear();
}


void TestRunner::run(RTF::TestResult &result) {
    interrupted = false;
    result.startTestRunner();
    for (TestIterator it=tests.begin(); it!=tests.end(); ++it) {
        if(interrupted)
            break;
        current = *it;
        (*it)->run(result);
    }
    result.endTestRunner();
    current = NULL;
}

void TestRunner::interrupt() {
    if(current)
        current->interrupt();
    interrupted = true;
}
