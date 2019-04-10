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


#ifndef ROBOTTESTINGFRAMEWORK_WEBPROGRESSLISTENER_IMPL_H
#define ROBOTTESTINGFRAMEWORK_WEBPROGRESSLISTENER_IMPL_H


#include <robottestingframework/TestListener.h>

#include <mongoose.h>
#include <mutex>
#include <thread>

namespace robottestingframework {

/**
 * \brief Singleton class WebProgressListenerImpl listens to any messages reported by the tests
 * during the test run, formates them sends them to the web clients.
 *
 * \ingroup key_class
 *
 */
class WebProgressListenerImpl
{
public:
    /**
     * create Creates an instance of WebProgressListenerImpl class
     * @param port the server port number. default is 8080
     * @param verbose enables the verbose mode. If \c true, the source file and
     * the line number where the messages are issued by the tests will be written to
     * the standard output. The verbose mode is disabled by default.
     */
    static WebProgressListenerImpl& create(unsigned int port = 8080,
                                           bool verbose = false);

    /**
     *  WebProgressListenerImpl destructor
     */
    virtual ~WebProgressListenerImpl();

    /**
     * This is called to report any arbitrary message
     * from tests.
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    virtual void addReport(const Test* test, TestMessage msg);

    /**
     * This is called when an error occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding error message
     */
    virtual void addError(const Test* test, TestMessage msg);

    /**
     * This is called when a failure occurred during test run
     * @param test pointer to the corresponding test
     * @param msg  correspoinding failure message
     */
    virtual void addFailure(const Test* test, TestMessage msg);

    /**
     * This is called when a Test is started
     * @param test pointer to the corresponding test
     */
    virtual void startTest(const Test* test);

    /**
     * This is called when a Test is finished
     * @param test pointer to the corresponding test
     */
    virtual void endTest(const Test* test);

    /**
     * This is called when a TestSuite is started
     * @param test pointer to the corresponding test
     */
    virtual void startTestSuite(const Test* test);

    /**
     * This is called when a TestSuite is finished
     * @param test pointer to the corresponding test
     */
    virtual void endTestSuite(const Test* test);

    /**
     * This is called when the TestRunner is started
     */
    virtual void startTestRunner();

    /**
     * This is called when the TestRunner is finished
     */
    virtual void endTestRunner();

public:
    struct mg_server* server;
    std::mutex critical;
    bool shouldStop;
    std::string result;
    std::string suite_name;
    std::size_t suite_size;

    enum class TestStatus
    {
        NotRun = 0,
        Running = 1,
        Failed = 2,
        Success = 3
    };

    std::vector<TestStatus> testStatus;

private:
    WebProgressListenerImpl(WebProgressListenerImpl const&) = delete;
    void operator=(WebProgressListenerImpl const&) = delete;

    WebProgressListenerImpl(unsigned int port,
                            bool verbose);
    std::string encode(const std::string& data);
    static void update(void* param);
    static int handler(struct mg_connection* conn,
                       enum mg_event ev);

private:
    std::thread* updater;
    bool verbose;
    unsigned int port;
};

} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_WEBPROGRESSLISTENER_IMPL_H
