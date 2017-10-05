// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#if defined(_MSC_VER)
  // see https://support.microsoft.com/kb/155196/en-us
  #define __RTF_STR2(x) #x
  #define __RTF_STR1(x) __RTF_STR2(x)
  #define __RTF_LOC __FILE__ "("__STR1__(__LINE__)")"
  #define RTF_COMPILER_MESSAGE(x) __pragma(message(__LOC__ " : msg" #x))
  #define RTF_COMPILER_WARNING(x) __pragma(message(__LOC__ " : warning msg" #x))
  #define RTF_COMPILER_ERROR(x)  __pragma(message(__LOC__ " : error msg" #x))
#elif defined(__GNUC__)
  // see https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html
  #define __RTF_DO_PRAGMA(x) _Pragma (#x)
  #define RTF_COMPILER_MESSAGE(x) __RTF_DO_PRAGMA(message #x)
  #define RTF_COMPILER_WARNING(x) __RTF_DO_PRAGMA(GCC warning #x)
  #define RTF_COMPILER_ERROR(x)  __RTF_DO_PRAGMA(GCC error #x)
#else
  #define RTF_COMPILER_MESSAGE(x)
  #define RTF_COMPILER_WARNING(x)
  #define RTF_COMPILER_ERROR(x)
#endif

#ifndef _RTF_TESTASSERTER_H
#define _RTF_TESTASSERTER_H


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
 * \param condition If this condition evaluates to \c true then the
 *                  test failed.
 */
#define RTF_ASSERT_FAIL_IF_TRUE(condition, message)\
    ( RTF::Asserter::fail(!condition,\
                          RTF::TestMessage(std::string("asserts failure on (") +\
                                           std::string(#condition) + ") with exception",\
                                           message,\
                                           RTF_SOURCEFILE(),\
                                           RTF_SOURCELINE())) )

/** Conditional assertion with throwing failure exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 */
#define RTF_ASSERT_FAIL_IF_FALSE(condition, message)\
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
 * \param condition If this condition evaluates to \c true then the
 *                  test failed.
 */
#define RTF_ASSERT_ERROR_IF_TRUE(condition, message)\
    ( RTF::Asserter::error(!condition,\
                          RTF::TestMessage(std::string("asserts error on (") +\
                                           std::string(#condition) + ") with exception",\
                                           message,\
                                           RTF_SOURCEFILE(),\
                                           RTF_SOURCELINE())) )

/** Conditional assertion with throwing error exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 */
#define RTF_ASSERT_ERROR_IF_FALSE(condition, message)\
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
    ( RTF::Asserter::report(RTF::TestMessage("reports",\
                                            message,\
                                            RTF_SOURCEFILE(),\
                                            RTF_SOURCELINE()), dynamic_cast<RTF::TestCase*>(this)) )

/** Conditional assertion with throwing failure exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 */
#define RTF_ASSERT_FAIL_IF(condition, message) \
    RTF_COMPILER_WARNING(RTF_ASSERT_FAIL_IF(condition, message) \
                    is deprecated and will be removed. Please substitute with \
                    RTF_ASSERT_FAIL_IF_[TRUE|FALSE](condition, message));\
    RTF_ASSERT_FAIL_IF_FALSE(condition, message)

/** Conditional assertion with throwing error exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 */
#define RTF_ASSERT_ERROR_IF(condition, message)\
    RTF_COMPILER_WARNING(RTF_ASSERT_ERROR_IF(condition, message) \
                    is deprecated and will be removed. Please substitute with \
                    RTF_ASSERT_ERROR_IF_[TRUE|FALSE](condition, message));\
    RTF_ASSERT_ERROR_IF_FALSE(condition, message)

/** Conditional failure report. RTF_TEST_FAIL_IF_FALSE does not throw any
 *  exception. It reports a failure message to the TestResult indiecating
 *  that the check on the corresponding condition evaluates to \c false.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 *
 * \note RTF_TEST_FAIL_IF_FALSE throws error exception if it is not called
 *       within a TestCase class.
 */
#define RTF_TEST_FAIL_IF_FALSE(condition, message)\
    ( RTF::Asserter::testFail(condition,\
                          RTF::TestMessage(std::string("checking (") +\
                                           std::string(#condition) + ")",\
                                           message,\
                                           RTF_SOURCEFILE(),\
                                           RTF_SOURCELINE()), dynamic_cast<RTF::TestCase*>(this)) )

/** Conditional failure report. RTF_TEST_FAIL_IF_TRUE does not throw any
 *  exception. It reports a failure message to the TestResult indiecating
 *  that the check on the corresponding condition evaluates to \c true.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c true then the
 *                  test failed.
 *
 * \note RTF_TEST_FAIL_IF_TRUE throws error exception if it is not called
 *       within a TestCase class.
 */
#define RTF_TEST_FAIL_IF_TRUE(condition, message)\
    ( RTF::Asserter::testFail(!condition,\
                          RTF::TestMessage(std::string("checking (") +\
                                           std::string(#condition) + ")",\
                                           message,\
                                           RTF_SOURCEFILE(),\
                                           RTF_SOURCELINE()), dynamic_cast<RTF::TestCase*>(this)) )

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
#define RTF_TEST_FAIL_IF(condition, message) \
    RTF_COMPILER_WARNING(RTF_TEST_FAIL_IF(condition, message) \
                    is deprecated and will be removed. Please substitute with \
                    RTF_TEST_FAIL_IF[TRUE|FALSE](condition, message));\
    RTF_TEST_FAIL_IF_FALSE(condition, message)


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
    ( RTF::Asserter::testCheck(condition,\
                          RTF::TestMessage("checks",\
                                           message,\
                                           RTF_SOURCEFILE(),\
                                           RTF_SOURCELINE()), dynamic_cast<RTF::TestCase*>(this)) )

#endif // _RTF_TESTASSERTER_H
