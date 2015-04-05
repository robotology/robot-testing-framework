// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <string.h>
#include <Asserter.h>
#include <WebProgressListener.h>
#include <WebProgressListener_impl.h>

using namespace std;
using namespace RTF;


#define BLUE    "<font color=\"blue\">"
#define GREEN   "<font color=\"green\">"
#define RED     "<font color=\"red\">"
#define GRAY    "<font color=\"gray\">"
#define ENDC    "</font>"

#define MSG_ERROR   RED   "[ERROR] " ENDC
#define MSG_FAIL    RED   "[FAIL]  " ENDC
#define MSG_REPORT  GREEN "[INFO]  " ENDC


RTF::WebProgressListenerImpl &WebProgressListenerImpl::create(unsigned int port,
                                                         bool verbose) {
    static WebProgressListenerImpl instance(port, verbose);
    return instance;
}

WebProgressListenerImpl::WebProgressListenerImpl(unsigned int port,
                                         bool verbose) {    
    this->verbose = verbose;
    this->port = port;
    server = mg_create_server(this, WebProgressListenerImpl::handler);
    if(server) {
        std::string port_str = Asserter::format("%d", port);
        mg_set_option(server,
                      "listening_port", port_str.c_str());
        shouldStop = false;
        updater = new tthread::thread(update, this);
    }
}

WebProgressListenerImpl::~WebProgressListenerImpl() {    
    shouldStop = true;
    // stop the pooling thread
    if(updater) {        
        updater->join();
        delete updater;
        updater = NULL;
    }
    // delete the web server
    if(server) {
        // ensure the last message delivery (?)
        mg_poll_server(server, 1000);
        mg_destroy_server(&server);
        server = NULL;
    }
}

void WebProgressListenerImpl::update(void *param) {
    WebProgressListenerImpl* web = (WebProgressListenerImpl*) param;
    while(!web->shouldStop) {
        mg_poll_server(web->server, 1000);
#ifdef _WIN32
		Sleep(1000);
#endif
	}
}

int WebProgressListenerImpl::handler(struct mg_connection *conn,
                                        enum mg_event ev) {
    WebProgressListenerImpl* web = (WebProgressListenerImpl*) conn->server_param;
    if(ev == MG_REQUEST) {
        std::string data;
        bool shouldStop;
        // update status
        web->critical.lock();
        shouldStop = web->shouldStop;
        web->critical.unlock();
        if(shouldStop)
            data = "<html><head></head><body><h1>Robot Testing Framework</h1><br><hr>";
        else
            data =
                   "<html><head>"
                   "<script>"
                   "     function refresh() {"
                   "             window.location.reload(true);"
                   "             setTimeout(refresh, 1000);"
                   "     }"
                   "     setTimeout(refresh, 1000);"
                   "</script>"
                   " </head><body><h1>Robot Testing Framework</h1><br><hr>";

        web->critical.lock();
        data += web->html;
        web->critical.unlock();
        data += string("</body></html>");
        mg_send_data(conn, data.c_str(), strlen(data.c_str()));
        return MG_TRUE;
    }
    else if (ev == MG_AUTH)
        return MG_TRUE;
    else
        return MG_FALSE;
}

std::string WebProgressListenerImpl::encode(const std::string& data) {
    std::string buffer;
    buffer.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
        switch(data[pos]) {
            case '&':  buffer.append("&amp;");       break;
            case '\"': buffer.append("&quot;");      break;
            case '\'': buffer.append("&apos;");      break;
            case '<':  buffer.append("&lt;");        break;
            case '>':  buffer.append("&gt;");        break;
            default:   buffer.append(&data[pos], 1); break;
        }
    }
    return buffer;
}

void WebProgressListenerImpl::addReport(const RTF::Test* test,
                                RTF::TestMessage msg) {
    string text = Asserter::format("<br> %s (%s) %s : %s.",
                                  MSG_REPORT,
                                  encode(test->getName()).c_str(),
                                  encode(msg.getMessage()).c_str(),
                                  encode(msg.getDetail()).c_str());
    critical.lock();
    html += text;
    critical.unlock();
    //if(verbose && msg.getSourceLineNumber() != 0)
    //    cout<<GRAY<<msg.getSourceFileName()<<" at "<<msg.getSourceLineNumber()<<"."<<ENDC<<endl<<endl;
}

void WebProgressListenerImpl::addError(const RTF::Test* test,
                               RTF::TestMessage msg) {
    string text = Asserter::format("<br> %s (%s) %s : %s.",
                                  MSG_ERROR,
                                  encode(test->getName()).c_str(),
                                  encode(msg.getMessage()).c_str(),
                                  encode(msg.getDetail()).c_str());
    critical.lock();
    html += text;
    critical.unlock();
}

void WebProgressListenerImpl::addFailure(const RTF::Test* test,
                                 RTF::TestMessage msg) {
    string text = Asserter::format("<br> %s (%s) %s : %s.",
                                  MSG_FAIL,
                                  encode(test->getName()).c_str(),
                                  encode(msg.getMessage()).c_str(),
                                  encode(msg.getDetail()).c_str());
    critical.lock();
    html += text;
    critical.unlock();
}

void WebProgressListenerImpl::startTest(const RTF::Test* test) {
    string text = Asserter::format("<br> %s Test case %s started... %s",
                                  BLUE,
                                  encode(test->getName()).c_str(),
                                  ENDC);    
    critical.lock();
    html += text;
    critical.unlock();
}

void WebProgressListenerImpl::endTest(const RTF::Test* test) {
    string text = Asserter::format("<br> %s Test case %s %s %s",
                                  BLUE,
                                  encode(test->getName()).c_str(),
                                  (test->succeeded()) ? "passed!" : "failed!",
                                  ENDC);    
    critical.lock();
    html += text;
    critical.unlock();
}

void WebProgressListenerImpl::startTestSuit(const RTF::Test* test) {
    string text = Asserter::format("<br> %s Test suite %s started... %s",
                                  BLUE,
                                  encode(test->getName()).c_str(),
                                  ENDC);    
    critical.lock();
    html += text;
    critical.unlock();
}

void WebProgressListenerImpl::endTestSuit(const RTF::Test* test) {
    string text = Asserter::format("<br> %s Test suite %s %s %s",
                                  BLUE,
                                  encode(test->getName()).c_str(),
                                  (test->succeeded()) ? "passed!" : "failed!",
                                  ENDC);    
    critical.lock();
    html += text;
    critical.unlock();
}

void WebProgressListenerImpl::startTestRunner() {
    string text = Asserter::format("<br> %s Staring test runner. %s",
                                  BLUE, ENDC);    
    critical.lock();
    html += text;
    critical.unlock();
}

void WebProgressListenerImpl::endTestRunner() {
    string text = Asserter::format("<br> %s Ending test runner. %s",
                                  BLUE, ENDC);    
    critical.lock();
    html += text;
    critical.unlock();
}



/**
 * WebProgressListener
 */
WebProgressListener::WebProgressListener(unsigned int port,
                                             bool verbose) {
    implement = & WebProgressListenerImpl::create(port, verbose);
}

WebProgressListener::~WebProgressListener() {
}

void WebProgressListener::addReport(const RTF::Test* test,
                                RTF::TestMessage msg) {
    ((WebProgressListener*)implement)->addReport(test, msg);
}

void WebProgressListener::addError(const RTF::Test* test,
                               RTF::TestMessage msg) {
    ((WebProgressListener*)implement)->addError(test, msg);
}

void WebProgressListener::addFailure(const RTF::Test* test,
                                 RTF::TestMessage msg) {
    ((WebProgressListener*)implement)->addFailure(test, msg);
}

void WebProgressListener::startTest(const RTF::Test* test) {
    ((WebProgressListener*)implement)->startTest(test);
}

void WebProgressListener::endTest(const RTF::Test* test) {
    ((WebProgressListener*)implement)->endTest(test);
}

void WebProgressListener::startTestSuit(const RTF::Test* test) {
    ((WebProgressListener*)implement)->startTestSuit(test);
}

void WebProgressListener::endTestSuit(const RTF::Test* test) {
    ((WebProgressListener*)implement)->endTestSuit(test);
}

void WebProgressListener::startTestRunner() {
    ((WebProgressListener*)implement)->startTestRunner();
}

void WebProgressListener::endTestRunner() {
    ((WebProgressListener*)implement)->endTestRunner();
}
