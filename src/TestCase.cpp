// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <TestMessage.h>
#include <TestCase.h>

using namespace RTF;


bool TestCase::setup() {
    return true;
}


void TestCase::tearDown() { }


void TestCase::run(RTF::TestResult &result) {
    this->result = &result;
    // call setup/run/tearDown
}

