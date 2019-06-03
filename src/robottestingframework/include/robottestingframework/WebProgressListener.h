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


#ifndef ROBOTTESTINGFRAMEWORK_WEBPROGRESSLISTENER_H
#define ROBOTTESTINGFRAMEWORK_WEBPROGRESSLISTENER_H

#include <robottestingframework/TestListener.h>

namespace robottestingframework {

/**
 * \brief class WebProgressListener listens to any messages reported by the tests
 * during the test run, formates them sends them to the web clients.
 *
 * \ingroup key_class
 *
 */
class WebProgressListener : public TestListener
{
public:
    /**
     * WebProgressListener constructor
     * @param port the server port number. default is 8080
     * @param verbose enables the verbose mode. If \c true, the source file and
     * the line number where the messages are issued by the tests will be written to
     * the standard output. The verbose mode is disabled by default.
     */
    WebProgressListener(unsigned int port = 8080,
                        bool verbose = false);

    /**
     *  WebProgressListener destructor
     */
    ~WebProgressListener() override;

    /**
     * This is called to report any arbitrary message
     * from tests.
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    void addReport(const Test* test, TestMessage msg) override;

    /**
     * This is called when an error occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    void addError(const Test* test, TestMessage msg) override;

    /**
     * This is called when a failure occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding failure message
     */
    void addFailure(const Test* test, TestMessage msg) override;

    /**
     * This is called when a Test is started
     * @param test pointer to the corresponding test
     */
    void startTest(const Test* test) override;

    /**
     * This is called when a Test is finished
     * @param test pointer to the corresponding test
     */
    void endTest(const Test* test) override;

    /**
     * This is called when a TestSuite is started
     * @param test pointer to the corresponding test
     */
    void startTestSuite(const Test* test) override;

    /**
     * This is called when a TestSuite is finished
     * @param test pointer to the corresponding test
     */
    void endTestSuite(const Test* test) override;

    /**
     * This is called when the TestRunner is started
     */
    void startTestRunner() override;

    /**
     * This is called when the TestRunner is finished
     */
    void endTestRunner() override;

private:
    void* implement;
};

} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_WEBPROGRESSLISTENER_H
