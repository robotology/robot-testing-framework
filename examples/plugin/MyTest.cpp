// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <TestAssert.h>
#include <SharedLibraryClass.h>

#include "MyTest.h"

using namespace RTF;

SHLIBPP_DEFINE_DEFAULT_SHARED_CLASS(MyTest)

MyTest::MyTest() : TestCase("MyTest") { }

MyTest::~MyTest() { }

bool MyTest::setup() {
    RTF_ASSERT_REPORT("running MyTest::setup...");
    return true;
}

void MyTest::tearDown() {
    RTF_ASSERT_REPORT("running MyTest::teardown...");
    // assert an arbitray error for example.
    RTF_ASSERT_ERROR("this is just for example!");
}

void MyTest::run() {
    RTF_ASSERT_REPORT("testing integers");
    RTF_ASSERT_CHECK(2<3, "is not smaller");
    int a = 5;
    int b = 3;
    RTF_ASSERT_CHECK(a<b, Asserter::format("%d is not smaller than %d.", a, b));
}
