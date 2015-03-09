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


void fail(RTF::TestMessage msg) {
    throw TestFailureException(msg);
}


void fail(bool condition,
          RTF::TestMessage msg) {
    if(!condition)
        throw TestFailureException(msg);
}


void error(RTF::TestMessage msg) {
    throw TestErrorException(msg);
}


void error(bool shouldFail,
          RTF::TestMessage msg) {
    if(shouldFail)
        throw TestErrorException(msg);
}

/*
void checkTrue(RTF::TestResult* result,
               RTF::TestMessage msg,
               bool condition) {
    if(!condition)
        result->addFailure(this, msg);
}
*/

