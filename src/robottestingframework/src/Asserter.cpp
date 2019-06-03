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


#include <robottestingframework/Asserter.h>
#include <robottestingframework/Exception.h>

#include <cstdarg>
#include <cstdio>

using namespace robottestingframework;


void Asserter::fail(TestMessage msg)
{
    throw TestFailureException(msg);
}


void Asserter::fail(bool condition,
                    TestMessage msg)
{
    if (!condition) {
        Asserter::fail(msg);
    }
}


void Asserter::error(TestMessage msg)
{
    throw TestErrorException(msg);
}


void Asserter::error(bool condition,
                     TestMessage msg)
{
    if (!condition) {
        Asserter::error(msg);
    }
}

void Asserter::report(TestMessage msg,
                      TestCase* testcase)
{
    if (testcase == nullptr) {
        Asserter::error(TestMessage("asserts error with exception",
                                    "Asserter::report is called outside a TestCase!",
                                    msg.getSourceFileName(),
                                    msg.getSourceLineNumber()));
        return;
    }
    testcase->getResult()->addReport(testcase, msg);
}

void Asserter::report(TestMessage msg,
                      TestSuite* testsuite)
{
    testsuite->getResult()->addReport(testsuite, msg);
}

void Asserter::testFail(bool condition,
                        TestMessage msg,
                        TestCase* testcase)
{
    if (testcase == nullptr) {
        Asserter::error(TestMessage("asserts error with exception",
                                    "Asserter::testFail is called outside a TestCase!",
                                    msg.getSourceFileName(),
                                    msg.getSourceLineNumber()));
        return;
    }
    if (!condition) {
        testcase->failed();
        testcase->getResult()->addFailure(testcase, msg);
    }
}

void Asserter::testCheck(bool condition,
                         TestMessage msg,
                         TestCase* testcase)
{
    if (testcase == nullptr) {
        Asserter::error(TestMessage("asserts error with exception",
                                    "Asserter::testCheck is called outside a TestCase!",
                                    msg.getSourceFileName(),
                                    msg.getSourceLineNumber()));
        return;
    }
    if (!condition) {
        testcase->failed();
        testcase->getResult()->addFailure(testcase, msg);
    } else {
        Asserter::report(msg, testcase);
    }
}

std::string Asserter::format(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    std::string str;
    if (msg != nullptr) {
        char buf[255];
        int w = vsnprintf(buf, 255, msg, args);
        str = buf;
    }
    va_end(args);
    return str;
}
