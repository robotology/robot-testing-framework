// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <stdlib.h>
#include <string>
#include <rtf/dll/Plugin.h>
#include <rtf/TestAssert.h>

#include "MyFixManager.h"

using namespace std;
using namespace RTF;

PREPARE_FIXTURE_PLUGIN(MyFixManager)

bool MyFixManager::setup(int argc, char** argv) {	
	RTF_ASSERT_ERROR_IF(argc >= 1, "missing paramter MY_FIXTURE_TEST_PARAM");
	RTF_ASSERT_ERROR_IF(string(argv[0]) == string("MY_FIXTURE_TEST_PARAM"), "missing paramter MY_FIXTURE_TEST_PARAM");
	RTF_ASSERT_ERROR_IF(putenv("MY_FIXTURE_TEST_SETUP=OK") == 0, "cannot set env variable MY_FIXTURE_TEST_SETUP");
    return true;
}

bool MyFixManager::check() {
	RTF_ASSERT_ERROR_IF(putenv("MY_FIXTURE_TEST_CHECK=OK") == 0, "cannot set env variable MY_FIXTURE_TEST_CHECK");
	return true;
}

void MyFixManager::tearDown() {
	getDispatcher()->fixtureCollapsed(TestMessage("COLAPSED"));
	RTF_ASSERT_ERROR_IF(putenv("MY_FIXTURE_TEST_TEARDOWN=OK") == 0, "cannot set env variable MY_FIXTURE_TEST_TEARDOWN");    
}

MyFixManager::~MyFixManager() {	
	// RTF_ASSERT_ERROR_IF(putenv("MY_FIXTURE_TEST_DELETE=OK") == 0, "cannot set env variable MY_FIXTURE_TEST_DELETE");
}
