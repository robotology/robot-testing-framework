// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_TESTASSERTER_H
#define _RTF_TESTASSERTER_H


#include <Asserter.h>


/** Assertion with throwing failure exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 */
#define RTF_ASSERT_FAIL(message)\
    ( RTF::Asserter::fail(RTF::TestMessage("asserts failure with exception",\
                                            message,\
                                            RTF_SOURCEFILE(),\
                                            RTF_SOURCELINE())) )


/** Conditional assertion with throwing failure exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 */
#define RTF_ASSERT_FAIL_IF(condition, message)\
    ( RTF::Asserter::fail(condition,\
                          RTF::TestMessage(std::string("asserts failure on (") +\
                                           std::string(#condition) + ") with exception",\
                                           message,\
                                           RTF_SOURCEFILE(),\
                                           RTF_SOURCELINE())) )


/** Assertion with throwing error exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 */
#define RTF_ASSERT_ERROR(message)\
    ( RTF::Asserter::error(RTF::TestMessage("asserts error with exception",\
                                            message,\
                                            RTF_SOURCEFILE(),\
                                            RTF_SOURCELINE())) )


/** Conditional assertion with throwing error exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 */
#define RTF_ASSERT_ERROR_IF(condition, message)\
    ( RTF::Asserter::error(condition,\
                          RTF::TestMessage(std::string("asserts error on (") +\
                                           std::string(#condition) + ") with exception",\
                                           message,\
                                           RTF_SOURCEFILE(),\
                                           RTF_SOURCELINE())) )


/** Reporting a message to the TestResult. RTF_REPORT does not
 *  throw any exception. It can be used to report any arbitrary message
 *  to the TestResult.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 *
 * \note RTF_REPORT throws error exception if it is not called
 *       within a TestCase class.
 */
#define RTF_REPORT(message)\
    if(dynamic_cast<RTF::TestCase*>(this) == 0) {\
        RTF_ASSERT_ERROR("RTF_REPORT is called outside a TestCase!"); }\
    RTF::Asserter::report(RTF::TestMessage("reports",\
                                            message,\
                                            RTF_SOURCEFILE(),\
                                            RTF_SOURCELINE()), dynamic_cast<RTF::TestCase*>(this))


/** Conditional failure report. RTF_ASSERT_CHECK does not throw any
 *  exception. It reports a failure message to the TestResult indiecating
 *  that the check on the corresponding condition evaluates to \c false.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 *
 * \note RTF_CHECK throws error exception if it is not called
 *       within a TestCase class.
 */
#define RTF_CHECK(condition, message)\
    if(dynamic_cast<RTF::TestCase*>(this) == 0) {\
        RTF_ASSERT_ERROR("RTF_CHECK is called outside a TestCase!"); }\
    RTF::Asserter::check(condition,\
                          RTF::TestMessage(std::string("checking (") +\
                                           std::string(#condition) + ")",\
                                           message,\
                                           RTF_SOURCEFILE(),\
                                           RTF_SOURCELINE()), dynamic_cast<RTF::TestCase*>(this))

#endif // _RTF_TESTASSERTER_H
