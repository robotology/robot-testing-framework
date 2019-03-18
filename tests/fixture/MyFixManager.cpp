/*
 * Robot Testing Framework
 *
 * Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include "MyFixManager.h"
#include <robottestingframework/TestAssert.h>
#include <robottestingframework/dll/Plugin.h>

#include <cstdlib>
#include <string>

using namespace std;
using namespace robottestingframework;

ROBOTTESTINGFRAMEWORK_PREPARE_FIXTURE_PLUGIN(MyFixManager)

bool MyFixManager::setup(int argc, char** argv)
{
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(argc >= 1, "missing paramter MY_FIXTURE_TEST_PARAM");
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(string(argv[0]) == string("MY_FIXTURE_TEST_PARAM"), "missing paramter MY_FIXTURE_TEST_PARAM");
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(putenv((char*)"MY_FIXTURE_TEST_SETUP=OK") == 0, "cannot set env variable MY_FIXTURE_TEST_SETUP");
    return true;
}

bool MyFixManager::check()
{
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(putenv((char*)"MY_FIXTURE_TEST_CHECK=OK") == 0, "cannot set env variable MY_FIXTURE_TEST_CHECK");
    return true;
}

void MyFixManager::tearDown()
{
    getDispatcher()->fixtureCollapsed(TestMessage("COLAPSED"));
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(putenv((char*)"MY_FIXTURE_TEST_TEARDOWN=OK") == 0, "cannot set env variable MY_FIXTURE_TEST_TEARDOWN");
}

MyFixManager::~MyFixManager()
{
    // ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(putenv("MY_FIXTURE_TEST_DELETE=OK") == 0, "cannot set env variable MY_FIXTURE_TEST_DELETE");
}
