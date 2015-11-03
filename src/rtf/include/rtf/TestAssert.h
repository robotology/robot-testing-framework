// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_TESTASSERTER_H
#define _RTF_TESTASSERTER_H

#include <rtf/rtf_config.h>
#include <rtf/Asserter.h>


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


/** Reporting a message to the TestResult. RTF_TEST_REPORT does not
 *  throw any exception. It can be used to report any arbitrary message
 *  to the TestResult.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 *
 * \note RTF_TEST_REPORT throws error exception if it is not called
 *       within a TestCase class.
 */
#define RTF_TEST_REPORT(message)\
    if(dynamic_cast<RTF::TestCase*>(this) == 0) {\
        RTF_ASSERT_ERROR("RTF_TEST_REPORT is called outside a TestCase!"); }\
    RTF::Asserter::report(RTF::TestMessage("reports",\
                                            message,\
                                            RTF_SOURCEFILE(),\
                                            RTF_SOURCELINE()), dynamic_cast<RTF::TestCase*>(this))


/** Conditional failure report. RTF_TEST_FAIL_IF does not throw any
 *  exception. It reports a failure message to the TestResult indiecating
 *  that the check on the corresponding condition evaluates to \c false.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 *
 * \note RTF_TEST_FAIL_IF throws error exception if it is not called
 *       within a TestCase class.
 */
#define RTF_TEST_FAIL_IF(condition, message)\
    if(dynamic_cast<RTF::TestCase*>(this) == 0) {\
        RTF_ASSERT_ERROR("RTF_TEST_FAIL_IF is called outside a TestCase!"); }\
    RTF::Asserter::testFail(condition,\
                          RTF::TestMessage(std::string("checking (") +\
                                           std::string(#condition) + ")",\
                                           message,\
                                           RTF_SOURCEFILE(),\
                                           RTF_SOURCELINE()), dynamic_cast<RTF::TestCase*>(this))

/** RTF_TEST_CHECK combines RTF_TEST_REPORT and RTF_TEST_FAIL_IF.
 * It does not throw any exception. It always reports the message (comment)
 * and marks the current check as [PASSED] or [FAILED] respectively
 * if the conditoin evalutes to \c true or \c false.
 * \ingroup Test Assertions
 * \param message Message to be reported as the comment for the current check
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 *
 * \note RTF_TEST_CHECK throws error exception if it is not called
 *       within a TestCase class.
 */
#define RTF_TEST_CHECK(condition, message)\
    if(dynamic_cast<RTF::TestCase*>(this) == 0) {\
        RTF_ASSERT_ERROR("RTF_TEST_CHECK is called outside a TestCase!"); }\
    RTF::Asserter::testCheck(condition,\
                          RTF::TestMessage("checks",\
                                           message,\
                                           RTF_SOURCEFILE(),\
                                           RTF_SOURCELINE()), dynamic_cast<RTF::TestCase*>(this))

#endif // _RTF_TESTASSERTER_H
