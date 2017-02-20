// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <rtf/TestAssert.h>
#include <rtf/dll/Plugin.h>
#include <rtf/WebProgressListener.h>
#include <rtf/TestRunner.h>
#include <rtf/TestSuit.h>

#include <sstream>

#ifndef _WIN32
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netdb.h>
    #include <unistd.h>
#endif

using namespace RTF;


class MyTest1 : public TestCase {
public:
    MyTest1() : TestCase("MyTest1") { }

    virtual void run() {
        RTF_TEST_CHECK(3<5, "smaller");
    }
};

class MyTest2 : public TestCase {
public:
    MyTest2() : TestCase("MyTest2") { }

    virtual void run() {
        RTF_TEST_CHECK(5==3, "equal");
    }
};

class WebProgListener : public RTF::TestCase {
public:
    WebProgListener() : TestCase("WebProgListener") {}

    virtual void run() {

        // create a test listener to collect the result
        WebProgressListener web(6543, true);


        // create a test result and add the listeners
        TestResult result;
        result.addListener(&web);

        // create a test suit and the test cases
        TestSuit suit("MyTestSuit");
        MyTest1 test1;
        MyTest2 test2;
        suit.addTest(&test1);
        suit.addTest(&test2);

        // create a test runner
        TestRunner runner;
        runner.addTest(&suit);
        runner.run(result);

        // checking the web socket
        struct sockaddr_in serv_addr;
        struct hostent *server;

        RTF_TEST_REPORT("openning client socket");
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);

#ifndef _WIN32
        struct timeval tv;
        tv.tv_sec = 3;
        tv.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
#endif
        RTF_ASSERT_FAIL_IF(sockfd >= 0, "opening socket");
        server = gethostbyname("localhost");
        RTF_ASSERT_FAIL_IF(server != NULL, "no such host");

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(6543);
        RTF_TEST_REPORT("Conneting to the web listener server");
        RTF_ASSERT_FAIL_IF(connect(sockfd,(struct sockaddr *)
                                   &serv_addr,sizeof(serv_addr)) >= 0, "connecting");

        char buffer[256] = "GET /status HTTP/1.0\r\n\r\n";
        RTF_TEST_REPORT("Writing to web listener server");
        RTF_ASSERT_FAIL_IF(write(sockfd, buffer, strlen(buffer)) >= 0, "writing to socket");
        bzero(buffer,256);
        RTF_TEST_REPORT("Reading from web listener server");
        RTF_ASSERT_FAIL_IF(read(sockfd,buffer,255) >0, "reading from socket");

        std::stringstream ssbuff(buffer);
        std::string line;
        while(std::getline(ssbuff, line, '\n')){
            if(line.size() && line[0]=='{')
                break;
        }

        RTF_TEST_CHECK(line.size()>2,"Cheking the json result size returned by web listener");
        line = line.substr(0, line.size()-1);
        RTF_TEST_CHECK(line=="{\"name\":\"MyTestSuit\",\"ntest\":2,\"nfail\":1,\"npass\":1}",
                       "Cheking the json result returned by web listener");
        close(sockfd);
    }
};

PREPARE_PLUGIN(WebProgListener)
