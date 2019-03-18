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
#include <robottestingframework/TestResultCollector.h>
#include <robottestingframework/TestRunner.h>
#include <robottestingframework/dll/Plugin.h>
#include <robottestingframework/python/PythonPluginLoader.h>

using namespace robottestingframework;
using namespace robottestingframework::plugin;

class PythonPlugin : public TestCase
{
private:
    PythonPluginLoader loader;
    TestCase* test;

public:
    PythonPlugin() :
            TestCase("PythonPlugin")
    {
    }

    bool setup(int argc, char** argv) override
    {
        ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(argc >= 2, "Missing python test file as argument");
        ROBOTTESTINGFRAMEWORK_TEST_REPORT(Asserter::format("Loading python file %s", argv[1]));
        test = loader.open(argv[1]);
        ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(test != NULL, Asserter::format("Cannot load %s", argv[1]));
        return true;
    }

    void run() override
    {

        TestResultCollector collector;

        // create a test result and add the listeners
        TestResult result;
        result.addListener(&collector);

        // calling a test case
        test->run(result);

        //ROBOTTESTINGFRAMEWORK_TEST_REPORT(Asserter::format("count: %d", collector.failedCount()));
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.passedCount() == 1, "Checking passed count");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(collector.failedCount() == 0, "Checking failed count");
    }
};

ROBOTTESTINGFRAMEWORK_PREPARE_PLUGIN(PythonPlugin)
