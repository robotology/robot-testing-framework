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


#include <robottestingframework/TestAssert.h>
#include <robottestingframework/TestCase.h>
#include <robottestingframework/dll/Plugin.h>

extern "C" void robottestingframework_test_create(void);
extern "C" bool robottestingframework_test_setup(const char* param);
extern "C" void robottestingframework_test_teardown(void);
extern "C" void robottestingframework_test_run(void);

static robottestingframework::TestCase* testInstance = NULL;

class AdaTest : public robottestingframework::TestCase
{
public:
    AdaTest() :
            TestCase("AdaTest")
    {
        testInstance = this;
        robottestingframework_test_create();
    }

    bool setup(int argc, char** argv) override
    {
        std::string param;
        for (int i = 0; i < argc; i++)
            param = param + std::string(argv[i]) + std::string(" ");
        return robottestingframework_test_setup(param.c_str());
    }

    void tearDown() override
    {
        robottestingframework_test_teardown();
    }

    void run() override
    {
        robottestingframework_test_run();
    }

    void setTestName(std::string name)
    {
        setName(name);
    }
};

ROBOTTESTINGFRAMEWORK_PREPARE_PLUGIN(AdaTest);

extern "C" void robottestingframework_test_setname(char* name)
{
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(testInstance, "testInstance is surprisingly NULL!");
    ((AdaTest*)testInstance)->setTestName(name);
}

extern "C" void robottestingframework_test_report(char* message)
{
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(testInstance, "testInstance is surprisingly NULL!");
    robottestingframework::Asserter::report(robottestingframework::TestMessage("reports",
                                                                               message,
                                                                               ROBOTTESTINGFRAMEWORK_SOURCEFILE(),
                                                                               ROBOTTESTINGFRAMEWORK_SOURCELINE()),
                                            testInstance);
}


extern "C" void robottestingframework_test_check(unsigned int condtion, char* message)
{
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(testInstance, "testInstance is surprisingly NULL!");
    robottestingframework::Asserter::testCheck(condtion != 0, robottestingframework::TestMessage("checks", message, ROBOTTESTINGFRAMEWORK_SOURCEFILE(), ROBOTTESTINGFRAMEWORK_SOURCELINE()), testInstance);
}


extern "C" void robottestingframework_test_fail_if(unsigned int condtion, char* message)
{
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(testInstance, "testInstance is surprisingly NULL!");
    robottestingframework::Asserter::testFail(condtion != 0, robottestingframework::TestMessage("checking condition", message, ROBOTTESTINGFRAMEWORK_SOURCEFILE(), ROBOTTESTINGFRAMEWORK_SOURCELINE()), testInstance);
}


extern "C" void robottestingframework_assert_fail(char* message)
{
    robottestingframework::Asserter::fail(robottestingframework::TestMessage("asserts failure with exception",
                                                                             message,
                                                                             ROBOTTESTINGFRAMEWORK_SOURCEFILE(),
                                                                             ROBOTTESTINGFRAMEWORK_SOURCELINE()));
}

extern "C" void robottestingframework_assert_error(char* message)
{
    robottestingframework::Asserter::error(robottestingframework::TestMessage("asserts error with exception",
                                                                              message,
                                                                              ROBOTTESTINGFRAMEWORK_SOURCEFILE(),
                                                                              ROBOTTESTINGFRAMEWORK_SOURCELINE()));
}
