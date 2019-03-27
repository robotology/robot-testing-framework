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


#ifndef ROBOTTESTINGFRAMEWORK_ASSERTER_H
#define ROBOTTESTINGFRAMEWORK_ASSERTER_H

#include <robottestingframework/Exception.h>
#include <robottestingframework/TestCase.h>
#include <robottestingframework/TestMessage.h>
#include <robottestingframework/TestSuite.h>

#if defined _MSC_VER && _MSC_VER <= 1800 //Visual Studio 12 or earlier has not [[noreturn]]
#    define ROBOTTESTINGFRAMEWORK_NORETURN __declspec(noreturn)
#else
#    define ROBOTTESTINGFRAMEWORK_NORETURN [[noreturn]]
#endif


namespace robottestingframework {

/**
 * \ingroup key_class
 *
 * \brief The Asserter class is used to throw exception or to report messages/failures
 * to a TestResult.
 * \note There are many usefull macros in the TestAssert.h which can be used to prepare
 * detailed messages of errors or test failures.
 */
class Asserter
{
public:
    /**
     * @brief fail Throw a failure exception with the
     * given message.
     * @param msg The corresponding failure message
     */
    ROBOTTESTINGFRAMEWORK_NORETURN static void fail(TestMessage msg);

    /**
     * @brief fail Throw a failure exception if the
     * condition is not hold (it is not true).
     * @param condition The boolean expression
     * @param msg The corresponding failure message
     */
    static void fail(bool condition,
                     TestMessage msg);

    /**
     * @brief error Throw an error exception with the
     * given message.
     * @param msg The corresponding error message
     */
    ROBOTTESTINGFRAMEWORK_NORETURN static void error(TestMessage msg);

    /**
     * @brief error Throw an error exception if the
     * condition is not hold (it is not true).
     * @param condition The boolean expression
     * @param msg The corresponding error message
     */
    static void error(bool condition,
                      TestMessage msg);

    /**
     * @brief report report a message to the
     * result collector of the given TestSuite
     * @param msg The corresponding message
     * @param testsuite The owner of the message (reporter)
     * @note report does not throw any exception!
     */
    static void report(TestMessage msg,
                       TestSuite* testsuite);

    /**
     * @brief report report a message to the
     * result collector of the given TestCase
     * @param msg The corresponding message
     * @param testcase The owner of the message (reporter)
     * @note report does not throw any exception!
     */
    static void report(TestMessage msg,
                       TestCase* testcase);

    /**
     * @brief Checks the given boolean condition
     * and if it is not hold (it is not true) a failure
     * message will be added to the result collector.
     * @param condition The boolean expression
     * @param msg The corresponding message
     * @param testcase The owner of the message (reporter)
     * @note This does not throw any exception!
     */
    static void testFail(bool condition,
                         TestMessage msg,
                         TestCase* testcase);

    /**
     * @brief Checks the given boolean condition
     * and if it is not hold (it is not true) a failure
     * message will be added to the result collector;
     * otherwise only the message will be reported.
     * @param condition The boolean expression
     * @param msg The corresponding message
     * @param testcase The owner of the message (reporter)
     * @note This does not throw any exception!
     */
    static void testCheck(bool condition,
                          TestMessage msg,
                          TestCase* testcase);

    /**
     * @brief format can be used to format data to in
     *        the same way that \c sprintf formats.
     * @param msg a format-control string
     * @return the formated std::string
     */
    static std::string format(const char* msg, ...);
};

} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_ASSERTER_H
