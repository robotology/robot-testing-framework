// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_CONSOLELISTENER_H
#define _RTF_CONSOLELISTENER_H

#include <rtf/rtf_config.h>
#include <rtf/TestListener.h>

namespace RTF {
    class ConsoleListener;
}


/**
 * \brief class ConsoleListener listens to any messages reported by the tests
 * during the test run, formates them and print them to the standard output.
 *
 * \ingroup key_class
 *
 * Here's an example of using a ConsoleListener:
 * \include examples/simple.cpp
 */
class RTF_API RTF::ConsoleListener : public RTF::TestListener {
public:

    /**
     * ConsoleListener constructor
     *
     * @param verbose enables the verbose mode. If \c true, the source file and
     * the line number where the messages are issued by the tests will be written to
     * the standard output. The verbose mode is disabled by default.
     */
    ConsoleListener(bool verbose = false);

    /**
     * @brief hideUncriticalMessages hides the tests report messages and
     * only shows the test assertion failure and error messages.
     */
    void hideUncriticalMessages();

    /**
     *  ConsoleListener destructor
     */
    virtual ~ConsoleListener();

    /**
     * This is called to report any arbitrary message
     * from tests.
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    virtual void addReport(const RTF::Test* test, RTF::TestMessage msg);

    /**
     * This is called when an error occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    virtual void addError(const RTF::Test* test, RTF::TestMessage msg);

    /**
     * This is called when a failure occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding failure message
     */
    virtual void addFailure(const RTF::Test* test, RTF::TestMessage msg);

    /**
     * This is called when a Test is started
     * @param test pointer to the corresponding test
     */
    virtual void startTest(const RTF::Test* test);

    /**
     * This is called when a Test is finished
     * @param test pointer to the corresponding test
     */
    virtual void endTest(const RTF::Test* test);

    /**
     * This is called when a TestSuite is started
     * @param test pointer to the corresponding test
     */
    virtual void startTestSuite(const RTF::Test* test);

    /**
     * This is called when a TestSuite is finished
     * @param test pointer to the corresponding test
     */
    virtual void endTestSuite(const RTF::Test* test);

    /**
     * This is called when the TestRunner is started
     */
    virtual void startTestRunner();

    /**
     * This is called when the TestRunner is finished
     */
    virtual void endTestRunner();

private:
    bool verbose;
    bool hideUncritical;
};
#endif // _RTF_CONSOLELISTENER_H
