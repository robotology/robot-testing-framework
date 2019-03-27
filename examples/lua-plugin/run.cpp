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


#include <robottestingframework/ConsoleListener.h>
#include <robottestingframework/TestCase.h>
#include <robottestingframework/TestResult.h>
#include <robottestingframework/TestRunner.h>
#include <robottestingframework/lua/LuaPluginLoader.h>

#include <stdio.h>


using namespace robottestingframework;
using namespace robottestingframework::plugin;

int main(int argc, char* argv[])
{

    if (argc < 2) {
        printf("Usage: %s <lua plugin file name>\n", argv[0]);
        printf("for example: %s mytest.lua\n", argv[0]);
        return 0;
    }

    // load the test case plugin
    printf("Loading the plugin... \n");
    LuaPluginLoader loader;
    TestCase* test = loader.open(argv[1]);
    if (test == NULL) {
        printf("%s\n", loader.getLastError().c_str());
        return 0;
    }

    // create a test listener to collect the result
    ConsoleListener listener(false);

    // create a test result and add the listeners
    TestResult result;
    result.addListener(&listener);

    // create a test runner and run the test case
    TestRunner runner;
    runner.addTest(test);
    runner.run(result);

    return 0;
}
