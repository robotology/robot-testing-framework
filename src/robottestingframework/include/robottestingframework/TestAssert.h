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


#ifndef ROBOTTESTINGFRAMEWORK_TESTASSERT_H
#define ROBOTTESTINGFRAMEWORK_TESTASSERT_H


#if defined(_MSC_VER)
// see https://support.microsoft.com/kb/155196/en-us
#    define __ROBOTTESTINGFRAMEWORK_STR2(x) #    x
#    define __ROBOTTESTINGFRAMEWORK_STR1(x) __ROBOTTESTINGFRAMEWORK_STR2(x)
#    define __ROBOTTESTINGFRAMEWORK_LOC __FILE__ "("__STR1__(__LINE__) ")"
#    define ROBOTTESTINGFRAMEWORK_COMPILER_MESSAGE(x) __pragma(message(__LOC__ " : msg" #    x))
#    define ROBOTTESTINGFRAMEWORK_COMPILER_WARNING(x) __pragma(message(__LOC__ " : warning msg" #    x))
#    define ROBOTTESTINGFRAMEWORK_COMPILER_ERROR(x) __pragma(message(__LOC__ " : error msg" #    x))
#elif defined(__GNUC__)
// see https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html
#    define __ROBOTTESTINGFRAMEWORK_DO_PRAGMA(x) _Pragma(#    x)
#    define ROBOTTESTINGFRAMEWORK_COMPILER_MESSAGE(x) __ROBOTTESTINGFRAMEWORK_DO_PRAGMA(message #    x)
#    define ROBOTTESTINGFRAMEWORK_COMPILER_WARNING(x) __ROBOTTESTINGFRAMEWORK_DO_PRAGMA(GCC warning #    x)
#    define ROBOTTESTINGFRAMEWORK_COMPILER_ERROR(x) __ROBOTTESTINGFRAMEWORK_DO_PRAGMA(GCC error #    x)
#else
#    define ROBOTTESTINGFRAMEWORK_COMPILER_MESSAGE(x)
#    define ROBOTTESTINGFRAMEWORK_COMPILER_WARNING(x)
#    define ROBOTTESTINGFRAMEWORK_COMPILER_ERROR(x)
#endif


#include <robottestingframework/Asserter.h>


/** Assertion with throwing failure exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 */
#define ROBOTTESTINGFRAMEWORK_ASSERT_FAIL(message)                                                                \
    (::robottestingframework::Asserter::fail(::robottestingframework::TestMessage("asserts failure with exception",   \
                                                                              message,                            \
                                                                              ROBOTTESTINGFRAMEWORK_SOURCEFILE(), \
                                                                              ROBOTTESTINGFRAMEWORK_SOURCELINE())))

/** Conditional assertion with throwing failure exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c true then the
 *                  test failed.
 */
#define ROBOTTESTINGFRAMEWORK_ASSERT_FAIL_IF_TRUE(condition, message)                                                                                             \
    (::robottestingframework::Asserter::fail(!condition,                                                                                                            \
                                           ::robottestingframework::TestMessage(std::string("asserts failure on (") + std::string(#condition) + ") with exception", \
                                                                              message,                                                                            \
                                                                              ROBOTTESTINGFRAMEWORK_SOURCEFILE(),                                                 \
                                                                              ROBOTTESTINGFRAMEWORK_SOURCELINE())))

/** Conditional assertion with throwing failure exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 */
#define ROBOTTESTINGFRAMEWORK_ASSERT_FAIL_IF_FALSE(condition, message)                                                                                            \
    (::robottestingframework::Asserter::fail(condition,                                                                                                             \
                                           ::robottestingframework::TestMessage(std::string("asserts failure on (") + std::string(#condition) + ") with exception", \
                                                                              message,                                                                            \
                                                                              ROBOTTESTINGFRAMEWORK_SOURCEFILE(),                                                 \
                                                                              ROBOTTESTINGFRAMEWORK_SOURCELINE())))

/** Assertion with throwing error exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 */
#define ROBOTTESTINGFRAMEWORK_ASSERT_ERROR(message)                                                                \
    (::robottestingframework::Asserter::error(::robottestingframework::TestMessage("asserts error with exception",     \
                                                                               message,                            \
                                                                               ROBOTTESTINGFRAMEWORK_SOURCEFILE(), \
                                                                               ROBOTTESTINGFRAMEWORK_SOURCELINE())))

/** Conditional assertion with throwing error exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c true then the
 *                  test failed.
 */
#define ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_TRUE(condition, message)                                                                                           \
    (::robottestingframework::Asserter::error(!condition,                                                                                                          \
                                            ::robottestingframework::TestMessage(std::string("asserts error on (") + std::string(#condition) + ") with exception", \
                                                                               message,                                                                          \
                                                                               ROBOTTESTINGFRAMEWORK_SOURCEFILE(),                                               \
                                                                               ROBOTTESTINGFRAMEWORK_SOURCELINE())))

/** Conditional assertion with throwing error exception.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 */
#define ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(condition, message)                                                                                          \
    (::robottestingframework::Asserter::error(condition,                                                                                                           \
                                            ::robottestingframework::TestMessage(std::string("asserts error on (") + std::string(#condition) + ") with exception", \
                                                                               message,                                                                          \
                                                                               ROBOTTESTINGFRAMEWORK_SOURCEFILE(),                                               \
                                                                               ROBOTTESTINGFRAMEWORK_SOURCELINE())))

/** Reporting a message to the TestResult. ROBOTTESTINGFRAMEWORK_TEST_REPORT
 *  does not throw any exception.
 *  It can be used to report any arbitrary message to the TestResult.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 *
 * \note ROBOTTESTINGFRAMEWORK_TEST_REPORT throws error exception if it is not called
 *       within a TestCase class.
 */
#define ROBOTTESTINGFRAMEWORK_TEST_REPORT(message)                                                                   \
    (::robottestingframework::Asserter::report(::robottestingframework::TestMessage("reports",                           \
                                                                                message,                             \
                                                                                ROBOTTESTINGFRAMEWORK_SOURCEFILE(),  \
                                                                                ROBOTTESTINGFRAMEWORK_SOURCELINE()), \
                                             dynamic_cast<::robottestingframework::TestCase*>(this)))

/** Conditional failure report. ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE does not throw any
 *  exception. It reports a failure message to the TestResult indiecating
 *  that the check on the corresponding condition evaluates to \c false.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 *
 * \note ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE throws error exception if it is not called
 *       within a TestCase class.
 */
#define ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE(condition, message)                                                                         \
    (::robottestingframework::Asserter::testFail(condition,                                                                                    \
                                               ::robottestingframework::TestMessage(std::string("checking (") + std::string(#condition) + ")", \
                                                                                  message,                                                   \
                                                                                  ROBOTTESTINGFRAMEWORK_SOURCEFILE(),                        \
                                                                                  ROBOTTESTINGFRAMEWORK_SOURCELINE()),                       \
                                               dynamic_cast<::robottestingframework::TestCase*>(this)))

/** Conditional failure report. ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_TRUE does not throw any
 *  exception. It reports a failure message to the TestResult indiecating
 *  that the check on the corresponding condition evaluates to \c true.
 * \ingroup Test Assertions
 * \param message Message to be reported as the detail of TestMessage
 * \param condition If this condition evaluates to \c true then the
 *                  test failed.
 *
 * \note ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_TRUE throws error exception if it is not called
 *       within a TestCase class.
 */
#define ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_TRUE(condition, message)                                                                          \
    (::robottestingframework::Asserter::testFail(!condition,                                                                                   \
                                               ::robottestingframework::TestMessage(std::string("checking (") + std::string(#condition) + ")", \
                                                                                  message,                                                   \
                                                                                  ROBOTTESTINGFRAMEWORK_SOURCEFILE(),                        \
                                                                                  ROBOTTESTINGFRAMEWORK_SOURCELINE()),                       \
                                               dynamic_cast<::robottestingframework::TestCase*>(this)))

/** ROBOTTESTINGFRAMEWORK_TEST_CHECK combines ROBOTTESTINGFRAMEWORK_TEST_REPORT and ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF.
 * It does not throw any exception. It always reports the message (comment)
 * and marks the current check as [PASSED] or [FAILED] respectively
 * if the conditoin evalutes to \c true or \c false.
 * \ingroup Test Assertions
 * \param message Message to be reported as the comment for the current check
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 *
 * \note ROBOTTESTINGFRAMEWORK_TEST_CHECK throws error exception if it is not called
 *       within a TestCase class.
 */
#define ROBOTTESTINGFRAMEWORK_TEST_CHECK(condition, message)                                                            \
    (::robottestingframework::Asserter::testCheck(condition,                                                              \
                                                ::robottestingframework::TestMessage("checks",                            \
                                                                                   message,                             \
                                                                                   ROBOTTESTINGFRAMEWORK_SOURCEFILE(),  \
                                                                                   ROBOTTESTINGFRAMEWORK_SOURCELINE()), \
                                                dynamic_cast<::robottestingframework::TestCase*>(this)))

#endif // ROBOTTESTINGFRAMEWORK_TESTASSERT_H
