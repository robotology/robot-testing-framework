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


#include <robottestingframework/TestResult.h>

using namespace robottestingframework;

#define CALL_LISTENERS(method, ...)                                            \
    for (const auto& listener : listeners) \
        listener->method(__VA_ARGS__);

TestResult::TestResult() = default;


TestResult::~TestResult()
{
    reset();
}


void TestResult::addListener(TestListener* listener)
{
    listeners.insert(listener);
}


void TestResult::removeListener(TestListener* listener)
{
    listeners.erase(listener);
}


void TestResult::reset()
{
    listeners.clear();
}

void TestResult::addReport(const Test* test, TestMessage msg)
{
    CALL_LISTENERS(addReport, test, msg);
}

void TestResult::addError(const Test* test, TestMessage msg)
{
    CALL_LISTENERS(addError, test, msg);
}

void TestResult::addFailure(const Test* test, TestMessage msg)
{
    CALL_LISTENERS(addFailure, test, msg);
}

void TestResult::startTest(const Test* test)
{
    CALL_LISTENERS(startTest, test);
}

void TestResult::endTest(const Test* test)
{
    CALL_LISTENERS(endTest, test);
}

void TestResult::startTestSuite(const Test* test)
{
    CALL_LISTENERS(startTestSuite, test);
}

void TestResult::endTestSuite(const Test* test)
{
    CALL_LISTENERS(endTestSuite, test);
}

void TestResult::startTestRunner()
{
    CALL_LISTENERS(startTestRunner);
}

void TestResult::endTestRunner()
{
    CALL_LISTENERS(endTestRunner);
}
