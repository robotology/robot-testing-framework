// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <rtf/TestAssert.h>
#include <rtf/dll/Plugin.h>

#include "MyTest.h"

using namespace RTF;

PREPARE_PLUGIN(MyTest)

MyTest::MyTest() : TestCase("MyTest") { }

MyTest::~MyTest() { }

bool MyTest::setup(int argc, char** argv) {
    RTF_TEST_REPORT("running MyTest::setup...");
    return true;
}

void MyTest::tearDown() {
    RTF_TEST_REPORT("running MyTest::teardown...");
    // assert an arbitray error for example.
    RTF_ASSERT_ERROR("this is just for example!");
}

void MyTest::run() {
    RTF_TEST_REPORT("testing integers");
    RTF_TEST_CHECK(2<3, "is not smaller");
    int a = 5;
    int b = 3;
    RTF_TEST_CHECK(a<b, Asserter::format("%d is not smaller than %d.", a, b));
}
