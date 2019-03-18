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


#include <robottestingframework/TestRunner.h>

#include <algorithm>

using namespace robottestingframework;


TestRunner::TestRunner() :
        current(nullptr)
{
}


TestRunner::~TestRunner()
{
    reset();
}


void TestRunner::addTest(Test* test)
{
    if (std::find(tests.begin(), tests.end(), test) == tests.end()) {
        tests.push_back(test);
    }
}


void TestRunner::removeTest(Test* test)
{
    for (size_t i = 0; i < tests.size(); i++) {
        tests.erase(tests.begin() + i);
    }
}

void TestRunner::reset()
{
    tests.clear();
}


void TestRunner::run(TestResult& result)
{
    interrupted = false;
    result.startTestRunner();
    for (TestIterator it = tests.begin(); it != tests.end(); ++it) {
        if (interrupted)
            break;
        current = *it;
        (*it)->run(result);
    }
    result.endTestRunner();
    current = nullptr;
}

void TestRunner::interrupt()
{
    if (current)
        current->interrupt();
    interrupted = true;
}
