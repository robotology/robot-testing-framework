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


#define BLUE    "<font color=\"blue\" style=\"font-weight: bold;\">"
#define GREEN   "<font color=\"green\" style=\"font-weight: bold;\">"
#define RED     "<font color=\"red\" style=\"font-weight: bold;\">"
#define GRAY    "<font color=\"gray\" style=\"font-weight: bold;\">"
#define ENDC    "</font>"

#define MSG_ERROR   RED   "[ERROR]&nbsp;" ENDC
#define MSG_FAIL    RED   "[FAIL]&nbsp;&nbsp;" ENDC
#define MSG_REPORT  GREEN "[INFO]&nbsp;&nbsp;" ENDC

static std::string html_page =
"<!DOCTYPE html>\n"
"<html>\n"
"<head>\n"
"<style>\n"
".font_h4 {\n"
"font: normal normal normal 36px/1.3em Arial,'ms pgothic',dotum,helvetica,sans-serif;\n"
"color: #1C1C1C; font-weight: bold; }\n"
"\n"
".font_1 {\n"
"font: normal normal bold 12px/1.3em Arial,'ms pgothic',dotum,helvetica,sans-serif;\n"
"color: #808080; }\n"
"\n"
".my_window {\n"
"position:absolute;\n"
"left:20px; right:20px;\n"
"background: #efefef; background-color: #efefef;\n"
"border: solid 1px #0088CB;\n"
"-webkit-border-radius: 4px; -moz-border-radius: 4px; border-radius: 4px;\n"
"font-family: 'Spinnaker' !important; list-style: none;\n"
"margin: 0 0 10px; padding: 5px; position: absolute;\n"
"box-shadow: 0 5px 15px 0 rgba(0,0,0,.4); }\n"
"</style>\n"
"\n"
"<script>\n"
"function update() {\n"
"    var xmlhttp;\n"
"    if (window.XMLHttpRequest) {\n"
"      xmlhttp=new XMLHttpRequest();\n"
"    }\n"
"    else {\n"
"        xmlhttp=new ActiveXObject(\"Microsoft.XMLHTTP\");\n"
"    }\n"
"    xmlhttp.onreadystatechange=function() {\n"
"        if (xmlhttp.readyState==4 && xmlhttp.status==200) {\n"
"            document.getElementById(\"result\").innerHTML=xmlhttp.responseText;\n"
"             if(document.getElementById(\"autoscroll\").checked == true) {\n"
"               document.getElementById(\"result\").scrollTop = document.getElementById(\"result\").scrollHeight;\n"
"             }\n"
"        }\n"
"    }\n"
"    xmlhttp.open(\"GET\",document.URL+\"update\",true);\n"
"    xmlhttp.send();\n"
"    setTimeout(update, 1000);\n"
"}\n"
"setTimeout(update, 1000);\n"
"</script>\n"
"</head>\n"
"<body bgcolor=\"#efefef\">\n"
"<div class=\"my_window\">\n"
"<h4 style=\"text-align: center; margin:0;\" class=\"font_h4\">Robot Testing Framework</h4>\n"
"</div>\n"
"<div class=\"my_window\" style=\"top:75px; height:80%; padding:5px\">"
"<div id=\"result\" style=\"top:0px; height:95%; overflow-y:scroll; background:#ffffff;\"></div>"
"<input align=\"right\" type=\"checkbox\" id=\"autoscroll\" checked/> auto scroll"
"</div>"
"<div style=\"top:94%; position:absolute; padding-left:20px;\">\n"
"<p class=\"font_1\">(C) 2015 iCub Facility, Istituto Italiano di Tecnologi</p>\n"
"</div>\n"
"</body>\n"
"</html>\n";

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
	}
}

int WebProgressListenerImpl::handler(struct mg_connection *conn,
                                        enum mg_event ev) {
    WebProgressListenerImpl* web = (WebProgressListenerImpl*) conn->server_param;
    if(ev == MG_REQUEST) {
        if (strcmp(conn->uri, "/update") == 0) {
            web->critical.lock();
            std::string data = web->result;
            web->critical.unlock();
            mg_send_header(conn, "Content-Type", "text/turtle");
            mg_send_header(conn, "Access-Control-Allow-Origin", "*");
            //mg_send_header(conn, "Content-Location", "mydata.ttl");
            mg_printf_data(conn, "%s", data.c_str());
        }
        else {
            mg_send_data(conn, html_page.c_str(), strlen(html_page.c_str()));
        }
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
    result += text;
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
    result += text;
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
    result += text;
    critical.unlock();
}

void WebProgressListenerImpl::startTest(const RTF::Test* test) {
    string text = Asserter::format("<br> %s Test case %s started... %s",
                                  BLUE,
                                  encode(test->getName()).c_str(),
                                  ENDC);    
    critical.lock();
    result += text;
    critical.unlock();
}

void WebProgressListenerImpl::endTest(const RTF::Test* test) {
    string text = Asserter::format("<br> %s Test case %s %s %s",
                                  BLUE,
                                  encode(test->getName()).c_str(),
                                  (test->succeeded()) ? "passed!" : "failed!",
                                  ENDC);    
    critical.lock();
    result += text;
    critical.unlock();
}

void WebProgressListenerImpl::startTestSuit(const RTF::Test* test) {
    string text = Asserter::format("<br> %s Test suite %s started... %s",
                                  BLUE,
                                  encode(test->getName()).c_str(),
                                  ENDC);    
    critical.lock();
    result += text;
    critical.unlock();
}

void WebProgressListenerImpl::endTestSuit(const RTF::Test* test) {
    string text = Asserter::format("<br> %s Test suite %s %s %s",
                                  BLUE,
                                  encode(test->getName()).c_str(),
                                  (test->succeeded()) ? "passed!" : "failed!",
                                  ENDC);    
    critical.lock();
    result += text;
    critical.unlock();
}

void WebProgressListenerImpl::startTestRunner() {
    string text = Asserter::format("<br> %s Staring test runner. %s",
                                  BLUE, ENDC);    
    critical.lock();
    result += text;
    critical.unlock();
}

void WebProgressListenerImpl::endTestRunner() {
    string text = Asserter::format("<br> %s Ending test runner. %s",
                                  BLUE, ENDC);    
    critical.lock();
    result += text;
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
