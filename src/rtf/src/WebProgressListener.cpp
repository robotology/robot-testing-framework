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
#include<Asserter.h>
#include <WebProgressListener.h>

using namespace std;
using namespace RTF;

#define BLUE    "\033[94m"
#define GREEN   "\033[92m"
#define ORANGE  "\033[93m"
#define RED     "\033[91m"
#define GRAY    "\033[30m"
#define ENDC    "\033[0m"

#define MSG_ERROR   RED   "[ERROR] " ENDC
#define MSG_FAIL    RED   "[FAIL]  " ENDC
#define MSG_REPORT  GREEN "[INFO]  " ENDC


void* WebProgressListener::implement = NULL;

static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
    WebProgressListener* web = (WebProgressListener*) conn->server_param;
    if(ev == MG_REQUEST) {
       //mg_send_header(conn, "Content-Type", "text/plain");
       //mg_printf_data(conn, "This is a reply from server instance # %s",
       //               web->getHtml().c_str());
       mg_send_data(conn, web->getHtml().c_str(), strlen(web->getHtml().c_str()));
      return MG_TRUE;
    }
    else if (ev == MG_AUTH)
      return MG_TRUE;
    else
      return MG_FALSE;
}


WebProgressListener::WebProgressListener(unsigned int port,
                                         bool verbose) {
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
    html =
            "<html><body><h1>Robot Testing Framework</h1><br>"
            "<br>"
            "Welcome..."
            "</body></html>";
    return html;
}

void WebProgressListener::addReport(const RTF::Test* test,
                                RTF::TestMessage msg) {
    cout<<MSG_REPORT<<"("<<test->getName()<<") "
        <<msg.getMessage()<<": "<<msg.getDetail()<<endl;
    if(verbose && msg.getSourceLineNumber() != 0)
        cout<<GRAY<<msg.getSourceFileName()<<" at "<<msg.getSourceLineNumber()<<"."<<ENDC<<endl<<endl;
}

void WebProgressListener::addError(const RTF::Test* test,
                               RTF::TestMessage msg) {
    cout<<MSG_ERROR<<"("<<test->getName()<<") "
        <<msg.getMessage()<<": "<<msg.getDetail()<<endl;
    if(verbose && msg.getSourceLineNumber() != 0)
        cout<<GRAY<<msg.getSourceFileName()<<" at "<<msg.getSourceLineNumber()<<"."<<ENDC<<endl<<endl;
}

void WebProgressListener::addFailure(const RTF::Test* test,
                                 RTF::TestMessage msg) {
    cout<<MSG_FAIL<<"("<<test->getName()<<") "
        <<msg.getMessage()<<": "<<msg.getDetail()<<endl;
    if(verbose && msg.getSourceLineNumber() != 0)
        cout<<GRAY<<msg.getSourceFileName()<<" at "<<msg.getSourceLineNumber()<<"."<<ENDC<<endl<<endl;
}

void WebProgressListener::startTest(const RTF::Test* test) {
    cout<<BLUE<<"Test case "<<test->getName()<<" started..."<<ENDC<<endl;
}

void WebProgressListener::endTest(const RTF::Test* test) {
    cout<<BLUE<<"Test case "<<test->getName();
    if(test->succeeded())
        cout<<" passed!"<<ENDC<<endl;
    else
        cout<<" failed!"<<ENDC<<endl;
}

void WebProgressListener::startTestSuit(const RTF::Test* test) {
    cout<<BLUE<<"Test suit "<<test->getName()<<" started..."<<ENDC<<endl;
}

void WebProgressListener::endTestSuit(const RTF::Test* test) {
    cout<<BLUE<<"Test suit "<<test->getName();
    if(test->succeeded())
        cout<<" passed!"<<ENDC<<endl;
    else
        cout<<" failed!"<<ENDC<<endl;
}

void WebProgressListener::startTestRunner() {
    cout<<BLUE<<"Staring test runner."<<ENDC<<endl;
}

void WebProgressListener::endTestRunner() {
    cout<<BLUE<<"Ending test runner."<<ENDC<<endl;
}

