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


#include <robottestingframework/TestAssert.h>
#include <robottestingframework/TestRunner.h>
#include <robottestingframework/TestSuite.h>
#include <robottestingframework/WebProgressListener.h>
#include <robottestingframework/dll/Plugin.h>

#include <sstream>

#ifndef _WIN32
#    include <netdb.h>
#    include <netinet/in.h>
#    include <sys/socket.h>
#    include <sys/types.h>
#    include <unistd.h>
#endif

using namespace robottestingframework;


class MyTest1 : public TestCase
{
public:
    MyTest1() :
            TestCase("MyTest1")
    {
    }

    void run() override
    {
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(3 < 5, "smaller");
    }
};

class MyTest2 : public TestCase
{
public:
    MyTest2() :
            TestCase("MyTest2")
    {
    }

    void run() override
    {
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(5 == 3, "equal");
    }
};

class WebProgListener : public TestCase
{
public:
    WebProgListener() :
            TestCase("WebProgListener")
    {
    }

    void run() override
    {

        // create a test listener to collect the result
        WebProgressListener web(6543, true);


        // create a test result and add the listeners
        TestResult result;
        result.addListener(&web);

        // create a test suite and the test cases
        TestSuite suite("MyTestSuite");
        MyTest1 test1;
        MyTest2 test2;
        suite.addTest(&test1);
        suite.addTest(&test2);

        // create a test runner
        TestRunner runner;
        runner.addTest(&suite);
        runner.run(result);

        // checking the web socket
        struct sockaddr_in serv_addr;
        struct hostent* server;

        ROBOTTESTINGFRAMEWORK_TEST_REPORT("openning client socket");
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);

#ifndef _WIN32
        struct timeval tv;
        tv.tv_sec = 3;
        tv.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));
#endif
        ROBOTTESTINGFRAMEWORK_ASSERT_FAIL_IF_FALSE(sockfd >= 0, "opening socket");
        server = gethostbyname("localhost");
        ROBOTTESTINGFRAMEWORK_ASSERT_FAIL_IF_FALSE(server != nullptr, "no such host");

        bzero((char*)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(6543);
        ROBOTTESTINGFRAMEWORK_TEST_REPORT("Conneting to the web listener server");
        ROBOTTESTINGFRAMEWORK_ASSERT_FAIL_IF_FALSE(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) >= 0, "connecting");

        char buffer[256] = "GET /status HTTP/1.0\r\n\r\n";
        ROBOTTESTINGFRAMEWORK_TEST_REPORT("Writing to web listener server");
        ROBOTTESTINGFRAMEWORK_ASSERT_FAIL_IF_FALSE(write(sockfd, buffer, strlen(buffer)) >= 0, "writing to socket");
        bzero(buffer, 256);
        ROBOTTESTINGFRAMEWORK_TEST_REPORT("Reading from web listener server");
        ROBOTTESTINGFRAMEWORK_ASSERT_FAIL_IF_FALSE(read(sockfd, buffer, 255) > 0, "reading from socket");

        std::stringstream ssbuff(buffer);
        std::string line;
        while (std::getline(ssbuff, line, '\n')) {
            if (line.size() && line[0] == '{')
                break;
        }

        ROBOTTESTINGFRAMEWORK_TEST_CHECK(line.size() > 2, "Cheking the json result size returned by web listener");
        line = line.substr(0, line.size() - 1);
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(line == "{\"name\":\"MyTestSuite\",\"testStatus\":[3,2]}",
                                         "Cheking the json result returned by web listener");
        close(sockfd);
    }
};

ROBOTTESTINGFRAMEWORK_PREPARE_PLUGIN(WebProgListener)
