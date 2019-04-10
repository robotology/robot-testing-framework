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


#include "MyTest.h"
#include <robottestingframework/TestAssert.h>
#include <robottestingframework/dll/Plugin.h>

using namespace robottestingframework;

ROBOTTESTINGFRAMEWORK_PREPARE_PLUGIN(MyTest)

MyTest::MyTest() :
        TestCase("MyTest")
{
}

bool MyTest::setup(int argc, char** argv)
{
    ROBOTTESTINGFRAMEWORK_TEST_REPORT("running MyTest::setup...");
    return true;
}

void MyTest::tearDown()
{
    ROBOTTESTINGFRAMEWORK_TEST_REPORT("running MyTest::teardown...");
    // assert an arbitray error for example.
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR("this is just for example!");
}

void MyTest::run()
{
    ROBOTTESTINGFRAMEWORK_TEST_REPORT("testing integers");
    ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE(2 < 3, "is not smaller");
    int a = 5;
    int b = 3;
    ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE(a < b, Asserter::format("%d is not smaller than %d.", a, b));
}
