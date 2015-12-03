// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <stdarg.h>
#include <stdio.h>

#include <rtf/Asserter.h>
#include <rtf/Exception.h>

using namespace RTF;


void Asserter::fail(RTF::TestMessage msg) {
    throw TestFailureException(msg);
}


void Asserter::fail(bool condition,
                    RTF::TestMessage msg) {
    if(!condition)
        throw TestFailureException(msg);
}


void Asserter::error(RTF::TestMessage msg) {
    throw TestErrorException(msg);
}


void Asserter::error(bool condition,
                     RTF::TestMessage msg)
{
    if(!condition)
        throw TestErrorException(msg);
}

void Asserter::report(RTF::TestMessage msg,
                      RTF::TestCase* testcase)
{
    if(testcase == 0) {
        RTF::Asserter::error(RTF::TestMessage("asserts error with exception",
                                              "Asserter::report is called outside a TestCase!",
                                              msg.getSourceFileName(),
                                              msg.getSourceLineNumber()));
        return;
    }
    testcase->getResult()->addReport(testcase, msg);
}

void Asserter::report(RTF::TestMessage msg,
                      RTF::TestSuit* testsuit)
{
    testsuit->getResult()->addReport(testsuit, msg);
}

void Asserter::testFail(bool condition,
                     RTF::TestMessage msg,
                     RTF::TestCase* testcase)
{
    if(testcase == 0) {
        RTF::Asserter::error(RTF::TestMessage("asserts error with exception",
                                              "Asserter::testFail is called outside a TestCase!",
                                              msg.getSourceFileName(),
                                              msg.getSourceLineNumber()));
        return;
    }
    if(!condition) {
        testcase->failed();
        testcase->getResult()->addFailure(testcase, msg);
    }
}

void Asserter::testCheck(bool condition,
                     RTF::TestMessage msg,
                     RTF::TestCase* testcase)
{
    if(testcase == 0) {
        RTF::Asserter::error(RTF::TestMessage("asserts error with exception",
                                              "Asserter::testCheck is called outside a TestCase!",
                                              msg.getSourceFileName(),
                                              msg.getSourceLineNumber()));
        return;
    }
    if(!condition) {
        testcase->failed();
        testcase->getResult()->addFailure(testcase, msg);
    }
    else
        Asserter::report(msg, testcase);
}

std::string Asserter::format(const char* msg, ...) {
    va_list args;
    va_start(args, msg);
    std::string str;
    if (msg) {
        char buf[255];
        int w = vsnprintf(buf, 255, msg, args);
        str = buf;
    }
    va_end(args);
    return str;
}
