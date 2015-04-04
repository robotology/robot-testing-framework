// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <string.h>
#include <iostream>
#include <mongoose.h>
#include <Asserter.h>
#include <WebProgressListener.h>

#ifdef _WIN32
#else
    #include <unistd.h>
#endif

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


void* WebProgressListener::implement = NULL;

static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
    WebProgressListener* web = (WebProgressListener*) conn->server_param;
    if(ev == MG_REQUEST) {
        web->setBusy(true);
       std::string data;
       if(web->isDone())
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
       data += web->getHtml();
       data += string("</body></html>");
       mg_send_data(conn, data.c_str(), strlen(web->getHtml().c_str()));
       web->setBusy(!web->isDone());
      return MG_TRUE;
    }
    else if (ev == MG_AUTH)
      return MG_TRUE;
    else
      return MG_FALSE;
}


WebProgressListener::WebProgressListener(unsigned int port,
                                         bool verbose) {
    done = busy = false;
    this->verbose = verbose;
    this->port = port;
    WebProgressListener::implement = mg_create_server(this, ev_handler);
    if(implement) {
        std::string port_str = Asserter::format("%d", port);
        mg_set_option((struct mg_server*)WebProgressListener::implement,
                      "listening_port", port_str.c_str());
          mg_start_thread(WebProgressListener::update,
                          (struct mg_server*)WebProgressListener::implement);
    }
}

WebProgressListener::~WebProgressListener() {
    while(busy) {
#ifdef _WIN32
        Sleep(1000);
#else
    sleep(1);
#endif
    }
    if(WebProgressListener::implement) {
          mg_destroy_server((struct mg_server**)(&WebProgressListener::implement));
          WebProgressListener::implement = NULL;
    }
}

void* WebProgressListener::update(void *server) {
    for (;;)
        mg_poll_server((struct mg_server *) server, 1000);
    return NULL;
}


std::string WebProgressListener::getHtml() {
    return html;
}

bool WebProgressListener::isDone() {
    return done;
}

bool WebProgressListener::setBusy(bool flag) {
    busy = flag;
}

void WebProgressListener::addReport(const RTF::Test* test,
                                RTF::TestMessage msg) {
    string text = Asserter::format("<br> %s (%s) %s : %s.",
                                  MSG_REPORT,
                                  test->getName().c_str(),
                                  msg.getMessage().c_str(),
                                  msg.getDetail().c_str());
    html += text;
    //if(verbose && msg.getSourceLineNumber() != 0)
    //    cout<<GRAY<<msg.getSourceFileName()<<" at "<<msg.getSourceLineNumber()<<"."<<ENDC<<endl<<endl;
}

void WebProgressListener::addError(const RTF::Test* test,
                               RTF::TestMessage msg) {
    string text = Asserter::format("<br> %s (%s) %s : %s.",
                                  MSG_ERROR,
                                  test->getName().c_str(),
                                  msg.getMessage().c_str(),
                                  msg.getDetail().c_str());
    html += text;
}

void WebProgressListener::addFailure(const RTF::Test* test,
                                 RTF::TestMessage msg) {
    string text = Asserter::format("<br> %s (%s) %s : %s.",
                                  MSG_FAIL,
                                  test->getName().c_str(),
                                  msg.getMessage().c_str(),
                                  msg.getDetail().c_str());
    html += text;
}

void WebProgressListener::startTest(const RTF::Test* test) {
    string text = Asserter::format("<br> %s Test case %s started... %s",
                                  BLUE,
                                  test->getName().c_str(),
                                  ENDC);
    html += text;
}

void WebProgressListener::endTest(const RTF::Test* test) {
    string text = Asserter::format("<br> %s Test case %s %s %s",
                                  BLUE,
                                  test->getName().c_str(),
                                  (test->succeeded()) ? "passed!" : "failed!",
                                  ENDC);
    html += text;
}

void WebProgressListener::startTestSuit(const RTF::Test* test) {
    string text = Asserter::format("<br> %s Test suite %s started... %s",
                                  BLUE,
                                  test->getName().c_str(),
                                  ENDC);
    html += text;
}

void WebProgressListener::endTestSuit(const RTF::Test* test) {
    string text = Asserter::format("<br> %s Test suite %s %s %s",
                                  BLUE,
                                  test->getName().c_str(),
                                  (test->succeeded()) ? "passed!" : "failed!",
                                  ENDC);
    html += text;
}

void WebProgressListener::startTestRunner() {
    string text = Asserter::format("<br> %s Staring test runner. %s",
                                  BLUE, ENDC);
    html += text;
}

void WebProgressListener::endTestRunner() {    
    string text = Asserter::format("<br> %s Ending test runner. %s",
                                  BLUE, ENDC);
    html += text;
    done = true;
}

