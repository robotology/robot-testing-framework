// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <Asserter.h>
#include <Exception.h>

using namespace RTF;


void Asserter::fail(RTF::TestMessage msg) {
    throw TestFailureException(msg);
}


void Asserter::fail(bool condition,
                    RTF::TestMessage msg) {
    if(!condition)
        throw TestFailureException(msg);
}


void Asserter::error(RTF::TestMessage msg) {
    throw TestErrorException(msg);
}


void Asserter::error(bool condition,
                     RTF::TestMessage msg)
{
    if(!condition)
        throw TestErrorException(msg);
}

void Asserter::report(RTF::TestMessage msg,
                      RTF::TestCase* testcase)
{
    testcase->getResult()->addReport(testcase, msg);
}

void Asserter::check(bool condition,
                     RTF::TestMessage msg,
                     RTF::TestCase* testcase)
{
    if(!condition) {
        testcase->getResult()->addFailure(testcase, msg);
    }
}
