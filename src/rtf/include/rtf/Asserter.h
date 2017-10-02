// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan and Lorenzo Natale
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_ASSERTER_H
#define _RTF_ASSERTER_H

#include <rtf/rtf_config.h>
#include <rtf/Exception.h>
#include <rtf/TestMessage.h>
#include <rtf/TestCase.h>
#include <rtf/TestSuite.h>

namespace RTF {
    class Asserter;
}

/**
 * \ingroup key_class
 *
 * \brief The Asserter class is used to throw exception or to report messages/failures
 * to a TestResult.
 * \note There are many usefull macros in the TestAssert.h which can be used to prepare
 * detailed messages of errors or test failures.
 */
class RTF::Asserter {

public:
    /**
     * @brief fail Throw a failure exception with the
     * given message.
     * @param msg The corresponding failure message
     */
    static RTF_API void fail RTF_NORETURN (RTF::TestMessage msg);

    /**
     * @brief fail Throw a failure exception if the
     * condition is not hold (it is not true).
     * @param condition The boolean expression
     * @param msg The corresponding failure message
     */
    static RTF_API void fail RTF_NORETURN (bool condition,
                       RTF::TestMessage msg);

    /**
     * @brief error Throw an error exception with the
     * given message.
     * @param msg The corresponding error message
     */
    static RTF_API void error RTF_NORETURN (RTF::TestMessage msg);

    /**
     * @brief error Throw an error exception if the
     * condition is not hold (it is not true).
     * @param condition The boolean expression
     * @param msg The corresponding error message
     */
    static RTF_API void error RTF_NORETURN (bool condition,
                       RTF::TestMessage msg);

    /**
     * @brief report report a message to the
     * result collector of the given TestSuit
     * @param msg The corresponding message
     * @param testsuite The owner of the message (reporter)
     * @note report does not throw any exception!
     */
    static RTF_API void report(RTF::TestMessage msg,
                        RTF::TestSuite* testsuite);

    /**
     * @brief report report a message to the
     * result collector of the given TestCase
     * @param msg The corresponding message
     * @param testcase The owner of the message (reporter)
     * @note report does not throw any exception!
     */
    static RTF_API void report(RTF::TestMessage msg,
                        RTF::TestCase* testcase);

    /**
     * @brief Checks the given boolean condition
     * and if it is not hold (it is not true) a failure
     * message will be added to the result collector.
     * @param condition The boolean expression
     * @param msg The corresponding message
     * @param testcase The owner of the message (reporter)
     * @note This does not throw any exception!
     */
    static RTF_API void testFail(bool condition,
                      RTF::TestMessage msg,
                      RTF::TestCase* testcase);

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
    static RTF_API void testCheck(bool condition,
                      RTF::TestMessage msg,
                      RTF::TestCase* testcase);

    /**
     * @brief format can be used to format data to in
     *        the same way that \c sprintf formats.
     * @param msg a format-control string
     * @return the formated std::string
     */
    static RTF_API std::string format(const char* msg, ...);
};

#endif // _RTF_ASSERTER_H
