// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <string.h>
#include <rtf/Asserter.h>
#include <rtf/WebProgressListener.h>
#include <rtf/impl/WebProgressListener_impl.h>

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
"<div class=\"my_window\" style=\"height:52px\">\n"
"<div style=\"position:relative; padding:5px; float:left;\"> <img src=\"data:image/png;base64,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\"/> </div>\n"
"<div style=\"position:relative; padding:5px; float:center;\"> <h4 style=\"text-align: center; margin:0;\" class=\"font_h4\">Robot Testing Framework</h4></div>\n"
"</div>\n"
"<div class=\"my_window\" style=\"top:75px; height:80%; padding:5px\">"
"<div id=\"result\" style=\"top:0px; height:95%; overflow-y:scroll; background:#ffffff;\"></div>"
"<input align=\"right\" type=\"checkbox\" id=\"autoscroll\" checked/> auto scroll"
"</div>"
"<div style=\"top:94%; position:absolute; padding-left:20px;\">\n"
"<p class=\"font_1\">(C) 2015 iCub Facility, Istituto Italiano di Tecnologia</p>\n"
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
