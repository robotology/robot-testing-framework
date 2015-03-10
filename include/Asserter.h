// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_ASSERTER_H
#define _RTF_ASSERTER_H


#include <Exception.h>
#include <TestMessage.h>
#include <TestCase.h>

namespace RTF {
    class Asserter;
}

class RTF::Asserter {

//    static void report(RTF::TestResult* result,
//                        RTF::TestMessage msg);

    static void fail(RTF::TestMessage msg);

    static void fail(bool condition,
                       RTF::TestMessage msg);

    static void error(RTF::TestMessage msg);

    static void error(bool condition,
                       RTF::TestMessage msg);

    static void report(RTF::TestMessage msg,
                        RTF::TestCase* testcase);

    static void check(bool condition,
                      RTF::TestMessage msg,
                      RTF::TestCase* testcase);
};


#define RTF_ASSERT_FAIL(message)\
    ( RTF::Asserter::fail(RTF::TestMessage("assert failed",\
                                            message,\
                                            RTF_SOURCEFILE(),\
                                            RTF_SOURCELINE())) )


#define RTF_ASSERT_FAIL_IF(condition, message)\
    ( RTF::Asserter::fail(condition,\
                          RTF::TestMessage(std::string("assert failed on (") +\
                                           std::string(#condition) + ")",\
                                           message,\
                                           RTF_SOURCEFILE(),\
                                           RTF_SOURCELINE())) )


#define RTF_ASSERT_ERROR(message)\
    ( RTF::Asserter::error(RTF::TestMessage("assert error",\
                                            message,\
                                            RTF_SOURCEFILE(),\
                                            RTF_SOURCELINE())) )


#define RTF_ASSERT_ERROR_IF(condition, message)\
    ( RTF::Asserter::error(condition,\
                          RTF::TestMessage(std::string("assert error on (") +\
                                           std::string(#condition) + ")",\
                                           message,\
                                           RTF_SOURCEFILE(),\
                                           RTF_SOURCELINE())) )


#define RTF_ASSERT_CHECK(condition, message)\
    ( RTF::Asserter::check(condition,\
                          RTF::TestMessage(std::string("assert check on (") +\
                                           std::string(#condition) + ")",\
                                           message,\
                                           RTF_SOURCEFILE(),\
                                           RTF_SOURCELINE())) )

#endif // _RTF_ASSERTER_H
