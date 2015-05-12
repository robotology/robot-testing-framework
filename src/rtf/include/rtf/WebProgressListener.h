// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_WEBPROGRESSLISTENER_H
#define _RTF_WEBPROGRESSLISTENER_H

#include <rtf/rtf_config.h>
#include <rtf/TestListener.h>

namespace RTF {
    class WebProgressListener;
}


/**
 * \brief class WebProgressListener listens to any messages reported by the tests
 * during the test run, formates them sends them to the web clients.
 *
 * \ingroup key_class
 *
 */
class RTF_API RTF::WebProgressListener : public RTF::TestListener {
public:

    /**
     * WebProgressListener constructor
     * @param port the server port number. default is 8080
     * @param verbose enables the verbose mode. If \c true, the source file and
     * the line number where the messages are issued by the tests will be written to
     * the standard output. The verbose mode is disabled by default.
     */
    WebProgressListener(unsigned int port=8080,
                        bool verbose = false);

    /**
     *  WebProgressListener destructor
     */
    virtual ~WebProgressListener();

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
     * This is called when a TestSuit is started
     * @param test pointer to the corresponding test
     */
    virtual void startTestSuit(const RTF::Test* test);

    /**
     * This is called when a TestSuit is finished
     * @param test pointer to the corresponding test
     */
    virtual void endTestSuit(const RTF::Test* test);

    /**
     * This is called when the TestRunner is started
     */
    virtual void startTestRunner();

    /**
     * This is called when the TestRunner is finished
     */
    virtual void endTestRunner();

private:
    void* implement;
};
#endif // _RTF_WEBPROGRESSLISTENER_H
